// //
// //  AirSenseFirmware.ino
// //  AirSense Firmware
// //
// //  Created by Aditya Pandya
// //

#include "Config.h"
#include "Logger.h"
#include "DeviceInfo.h"
#include "Protocol.h"
#include "SerialManager.h"

unsigned long lastHeartbeat = 0;

void setup()
{
    Logger::begin();

    Logger::info("Boot Complete");

    DeviceInfo device;

    device.deviceName = DEVICE_NAME;
    device.firmwareVersion = FIRMWARE_VERSION;
    device.chipModel = ESP.getChipModel();

    device.status = "READY";
    device.personCount = 0;
    device.petCount = 0;
    device.freeHeap = ESP.getFreeHeap();
    device.uptime = 0;

    Logger::info("Device Model Created");

    SerialManager::begin();

    
}

void loop()
{
   if (Serial.available())
{
    String message = Serial.readStringUntil('\n');

    message.trim();

    if (message == "PING")
    {
        Serial.println("PONG");
    }
}
}



