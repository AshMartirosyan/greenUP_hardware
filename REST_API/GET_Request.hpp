#pragma once
#include <Arduino.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

String GET_HARDWARE_URL = "http://192.168.1.7:3000/hardware";

String getRequest(String token)
{
    if (token == "")
    {
        return "No Token";
    }
    WiFiMulti *wifiMulti = new WiFiMulti();
    if (wifiMulti->run() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(GET_HARDWARE_URL);
        http.addHeader("Token", token);

        if (http.GET() == HTTP_CODE_OK)
        {
            return http.getString();
        }
        else
        {
            String errorString = http.errorToString(http.GET()).c_str();
            Serial.printf("[HTTP] GET... failed, error: %s\n", errorString);
            return "[HTTP] GET... failed, error: " + errorString;
        }
        http.end();
    }
    else
    {
        Serial.print("Not connected to internet\n");
        return "Not Connected to internet";
    }

    delete wifiMulti;
}
