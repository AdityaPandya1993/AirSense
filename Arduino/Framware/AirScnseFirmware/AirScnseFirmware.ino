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
#include "WiFiManager.h"
#include "CSIReceiver.h"
#include "CSIDriver.h"
#include "RawCSIRecorder.h"
#include "PacketAnalyzer.h"

unsigned long lastHeartbeat = 0;

void setup()
{
    Logger::begin();

    Logger::info("Boot Complete");

    WiFiManager::shared().begin();

    RawCSIRecorder::shared().begin();

    CSIDriver::shared().begin();

    CSIReceiver::shared().begin();

    PacketAnalyzer::shared().begin();

    Logger::info("WiFi Initialized");

    DeviceInfo device;

    device.deviceName = DEVICE_NAME;
    device.firmwareVersion = FIRMWARE_VERSION;
    device.chipModel = ESP.getChipModel();

    device.status = "READY";
    device.personCount = 0;
    device.petCount = 0;
    device.freeHeap = ESP.getFreeHeap();
    device.uptime = 0;

    Serial.print("CSI Ready = ");

    Serial.println(
    CSIReceiver::shared().isEnabled()
        ? "YES"
        : "NO"
);

    Logger::info("Device Model Created");



    SerialManager::begin();

    DeviceController::shared().setPersonCount(2);

    DeviceController::shared().setMotion("Walking");

    DeviceController::shared().setHeartRate(81);

    DeviceController::shared().setBreathing(18);

    Serial.print("WiFi Ready = ");

Serial.println(
    WiFiManager::shared().isReady()
        ? "YES"
        : "NO"
);
}

void loop()
{
    SimulationEngine::update();
    
    SerialManager::processIncomingCommand();

    PacketAnalyzer::shared().analyze(
    RawCSIRecorder::shared().latestFrame()
);

    if (millis() - lastHeartbeat >= 1000)
    {
        lastHeartbeat = millis();

        SerialManager::sendHeartbeat();
    }
}


