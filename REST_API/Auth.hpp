#pragma once
#include <Arduino.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <base64.h>
#include "../Classes/Functionality.hpp"

String AUTH_URL = "http://192.168.1.3:3000/auth";

String getToken(WiFiMulti &wifiMulti, String username, String password)
{
    HTTPClient http;
    if (wifiMulti.run() == WL_CONNECTED)
    {
        String loginString = username + ':' + password;
        String loginBase64String = base64::encode(loginString);
        String loginHeader = "Basic " + loginBase64String;

        http.begin(AUTH_URL);
        http.addHeader("Authorization", loginHeader);
        http.addHeader("device", "hardware");

        if (http.GET() == HTTP_CODE_OK)
        {
            return http.getString();
        }
        else
        {
            String error = http.errorToString(http.GET()).c_str();
            throw "[HTTP] GET... failed, error: " + error;
        }
        http.end();
    }
    else
    {
        throw "Not Connected to internet";
    }
}
