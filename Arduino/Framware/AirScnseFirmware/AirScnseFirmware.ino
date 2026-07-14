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
#include "DeviceController.h"
#include "SimulationEngine.h"

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

    DeviceController::shared().setPersonCount(2);

    DeviceController::shared().setMotion("Walking");

    DeviceController::shared().setHeartRate(81);

    DeviceController::shared().setBreathing(18);
}

void loop()
{
    SimulationEngine::update();
    
    SerialManager::processIncomingCommand();

    if (millis() - lastHeartbeat >= 1000)
    {
        lastHeartbeat = millis();

        SerialManager::sendHeartbeat();
    }
}


