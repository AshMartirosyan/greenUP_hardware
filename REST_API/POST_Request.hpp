#pragma once
#include <Arduino.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include "../Classes/Functionality.hpp"

String POST_HARDWARE_URL = "http://192.168.1.3:3000/hardware";

String postRequest(WiFiMulti &wifiMulti, String token, String data)
{
    HTTPClient http;
    if (wifiMulti.run() == WL_CONNECTED)
    {
        http.begin(POST_HARDWARE_URL);
        http.addHeader("x-access-token", token);
        http.addHeader("Content-type", "application/json");
        http.addHeader("device", "hardware");
        int responseCode = http.POST(data);

        if (responseCode == HTTP_CODE_OK)
        {
            String response = http.getString();
            Serial.print(response + "\n");
            return response;
        }
        if (responseCode == HTTP_CODE_UNAUTHORIZED)
        {
            throw responseCode;
        }
        else
        {
            String errorString = http.errorToString(responseCode).c_str();
            throw "[HTTP] POST... failed, error: " + errorString;
        }

        http.end();
    }
    else
    {
        throw "Not Connected to internet";
    }
}