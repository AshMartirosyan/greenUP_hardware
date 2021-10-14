#pragma once
#include <Arduino.h>
#include "Hardware.hpp"
#include <ArduinoJson.h>

namespace Functionality
{
    int getMoistureValue(Hardware &hardware);
    void changeValveState(Hardware &hardware);
    String createPostedData(int moistureValue, ValveState valveState, String id);
    template <class T>
    T getObjectFromJson(String json, String key);
} // namespace Functionality

int Functionality::getMoistureValue(Hardware &hardware)
{
    return map(analogRead(hardware.moisturePin), 550, 4095, 100, 0);
}

void Functionality::changeValveState(Hardware &hardware)
{
    if (hardware.valveState == CLOSE)
    {
        digitalWrite(hardware.relayPin, LOW);
        hardware.valveState = OPEN;
    }
    else
    {
        digitalWrite(hardware.relayPin, HIGH);
        hardware.valveState = CLOSE;
    }
}
template <class T>
T Functionality::getObjectFromJson(String json, String key)
{
    DynamicJsonDocument doc(256);
    deserializeJson(doc, json);
    return doc[key.c_str()].as<T>();
}

String Functionality::createPostedData(int moistureValue, ValveState valveState, String id)
{
    String json;
    DynamicJsonDocument doc(384);
    doc["moistureValue"] = moistureValue;
    doc["valveState"] = valveState;
    doc["_id"] = id;
    doc["location"] = "YEREVAN";
    serializeJson(doc, json);
    return json;
}
