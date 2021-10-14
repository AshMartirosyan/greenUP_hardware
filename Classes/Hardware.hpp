#pragma once
#include <Arduino.h>
#include <WiFiMulti.h>

enum ValveState
{
    OPEN,
    CLOSE
};

class Hardware
{
    String token = "";
    String id = "601153c202e9d241473b4ed1";

public:
    const String username = "admin";
    const String password = "admin";
    const int moisturePin = 33;
    const int relayPin = 13;
    ValveState valveState = CLOSE;

    // Hardware(const Hardware &h2)
    // {
    //     token = h2.token;
    //     valveState = h2.valveState;
    // }

    Hardware operator=(const Hardware &h2)
    {
        token = h2.token;
        valveState = h2.valveState;
    }

    void setToken(String token)
    {
        this->token = token;
    }
    String getToken()
    {
        return this->token;
    }
    String getId()
    {
        return this->id;
    }

    void setup()
    {
        pinMode(this->moisturePin, INPUT);
        pinMode(this->relayPin, OUTPUT);
    }
};