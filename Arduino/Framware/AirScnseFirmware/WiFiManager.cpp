//
//  WiFiManager.cpp
//  AirSense Firmware
//

#include "WiFiManager.h"
#include "Config.h"

#include <WiFi.h>

WiFiManager&
WiFiManager::shared()
{
    static WiFiManager manager;
    return manager;
}

WiFiManager::WiFiManager()
{
    _ready = false;
}

void WiFiManager::begin()
{
    Serial.println(">>>>>>>> ENTER WiFiManager::begin() <<<<<<<<");
    _ready = false;

    Serial.println();
    Serial.println("================================");
    Serial.println(" AirSense WiFi Manager");
    Serial.println("================================");

    //--------------------------------------------------
    // STA Mode
    //--------------------------------------------------

    WiFi.mode(WIFI_STA);

    delay(300);

    //--------------------------------------------------
    // Start Connection
    //--------------------------------------------------

    Serial.print("Connecting to : ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");

        delay(500);

        if (millis() - start > 20000)
        {
            Serial.println();
            Serial.println("WiFi Connection Timeout");

            Serial.print("Last Status : ");
            Serial.println(WiFi.status());

            _ready = false;

            return;
        }
    }

    //--------------------------------------------------
    // Connected
    //--------------------------------------------------

    Serial.println();
    Serial.println();
    Serial.println("WiFi Connected Successfully");

    Serial.print("SSID : ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    Serial.print("RSSI : ");
    Serial.println(WiFi.RSSI());

    Serial.print("Channel : ");
    Serial.println(WiFi.channel());

    Serial.print("MAC : ");
    Serial.println(WiFi.macAddress());

    _ready = true;
    Serial.println(">>>>>>>> EXIT WiFiManager::begin() <<<<<<<<");
}

bool WiFiManager::isReady() const
{
    return _ready;
}