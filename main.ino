#include "REST_API/Auth.hpp"
#include "REST_API/POST_Request.hpp"
#include "Classes/Functionality.hpp"
#include "WiFi.h"

#define uS_TO_S_FACTOR 1000000 // for converting to miliseconds
#define TIME_TO_SLEEP 1        //seconds

WiFiMulti wifiMulti;
Hardware hardware;

const String HOME_SSID = "Rostelecom_21887";
const String HOME_PASSWORD = "29c5f087";

const String ssid = "xntrendsuni";
const String wifiPassword = "trendsXN-2019!";

//RTC_DATA_ATTR char hardwareToken[256] = "Ashot";

void setup()
{
    Serial.begin(115200);

    hardware.setup();
    if (hardware.valveState == CLOSE)
    {
        digitalWrite(hardware.relayPin, HIGH);
    }
    else
    {
        digitalWrite(hardware.relayPin, LOW);
    }
    wifiMulti.addAP(HOME_SSID.c_str(), HOME_PASSWORD.c_str());
    if (wifiMulti.run() != WL_CONNECTED)
    {
        Serial.print("Cannot connet to wi-fi. Please chack wi-fi credentials\n");
    }

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop()
{

    if (hardware.getToken() == "")
    {
        try
        {
            String getResponse = getToken(wifiMulti, hardware.username, hardware.password);
            String token = Functionality::getObjectFromJson<String>(getResponse, "token");
            hardware.setToken(token);
        }
        catch (String error)
        {
            Serial.print(error + "\n");
        }
    }

    int moistureValue = Functionality::getMoistureValue(hardware);

    String id = hardware.getId();
    String data = Functionality::createPostedData(moistureValue, hardware.valveState, id);

    try
    {
        String postResponse = postRequest(wifiMulti, hardware.getToken(), data);
        int valveState = Functionality::getObjectFromJson<ValveState>(postResponse, "valveState");
        if (hardware.valveState != valveState)
        {
            Functionality::changeValveState(hardware);
        }
    }
    catch (int responseCode)
    {
        if (responseCode == HTTP_CODE_UNAUTHORIZED)
        {
            //If token expired
            try
            {
                String getResponse = getToken(wifiMulti, hardware.username, hardware.password);
                String token = Functionality::getObjectFromJson<String>(getResponse, "token");
                hardware.setToken(token);
                String postResponse = postRequest(wifiMulti, hardware.getToken(), data);
                int valveState = Functionality::getObjectFromJson<ValveState>(postResponse, "valveState");
                if (hardware.valveState != valveState)
                {
                    Functionality::changeValveState(hardware);
                }
            }
            catch (int errorCode)
            {
                Serial.print("Unhandled exception\n");
            }
            catch (String error)
            {
                Serial.print(error + "\n");
            }
        }
    }
    catch (String error)
    {
        Serial.println(error + "\n");
    }
    catch (...)
    {
        Serial.print("Unexpected error\n");
        return;
    }

    if (hardware.valveState == CLOSE)
    {
        esp_deep_sleep_start(); //Deep sleep
    }
}