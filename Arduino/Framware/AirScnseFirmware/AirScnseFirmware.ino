//
//  AirSenseFirmware.ino
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "Config.h"
#include "Logger.h"
#include "DeviceInfo.h"
#include "Protocol.h"
#include "SerialManager.h"
#include "DeviceController.h"

#include "WiFiManager.h"
#include "CSIReceiver.h"
#include "CSIDriver.h"
#include "RawCSIRecorder.h"

#include "PacketAnalyzer.h"

unsigned long lastHeartbeat = 0;

uint64_t lastAnalyzedPacketCount = 0;

////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////

void setup()
{
    //--------------------------------------------------
    // Logger
    //--------------------------------------------------

    Logger::begin();

    Logger::info("Boot Complete");

    //--------------------------------------------------
    // WiFi
    //--------------------------------------------------

    WiFiManager::shared().begin();

    //--------------------------------------------------
    // CSI Pipeline
    //--------------------------------------------------

    RawCSIRecorder::shared().begin();

    CSIDriver::shared().begin();

    CSIReceiver::shared().begin();

    PacketAnalyzer::shared().begin();

    Logger::info("WiFi Initialized");

    //--------------------------------------------------
    // Device Info
    //--------------------------------------------------

    DeviceInfo device;

    device.deviceName = DEVICE_NAME;
    device.firmwareVersion = FIRMWARE_VERSION;
    device.chipModel = ESP.getChipModel();

    device.status = "READY";
    device.personCount = 0;
    device.petCount = 0;
    device.freeHeap = ESP.getFreeHeap();
    device.uptime = 0;

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    Serial.print("CSI Ready = ");

    Serial.println(
        CSIReceiver::shared().isEnabled()
            ? "YES"
            : "NO"
    );

    Serial.print("WiFi Ready = ");

    Serial.println(
        WiFiManager::shared().isReady()
            ? "YES"
            : "NO"
    );

    Logger::info("Device Model Created");

    //--------------------------------------------------
    // Serial Protocol
    //--------------------------------------------------

    SerialManager::begin();

}

////////////////////////////////////////////////////////
// Loop
////////////////////////////////////////////////////////

void loop()
{
    //--------------------------------------------------
    // Incoming Commands
    //--------------------------------------------------

    SerialManager::processIncomingCommand();

    //--------------------------------------------------
    // Analyze Only New CSI Packet
    //--------------------------------------------------

    if (
        RawCSIRecorder::shared().hasFrame() &&
        RawCSIRecorder::shared().packetCount() != lastAnalyzedPacketCount
    )
    {
        lastAnalyzedPacketCount =
            RawCSIRecorder::shared().packetCount();

        PacketAnalyzer::shared().analyze(
            RawCSIRecorder::shared().latestFrame()
        );
    }

    //--------------------------------------------------
    // Heartbeat
    //--------------------------------------------------

    if (millis() - lastHeartbeat >= 1000)
    {
        lastHeartbeat = millis();

        SerialManager::sendHeartbeat();
    }
}