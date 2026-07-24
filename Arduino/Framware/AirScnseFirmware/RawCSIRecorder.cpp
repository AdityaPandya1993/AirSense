//
//  RawCSIRecorder.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "RawCSIRecorder.h"

#include <Arduino.h>

//--------------------------------------------------
// Guards concurrent access between the async ESP32
// Wi-Fi CSI hardware callback (record()) and the
// main loop reading the latest frame (latestFrame()).
// Without this, a reader could see a torn / partially
// overwritten frame if a new packet arrives mid-copy.
//--------------------------------------------------

static portMUX_TYPE rawCSIFrameMux = portMUX_INITIALIZER_UNLOCKED;

RawCSIRecorder&
RawCSIRecorder::shared()
{
    static RawCSIRecorder recorder;

    return recorder;
}

RawCSIRecorder::RawCSIRecorder()
{
    _packetCount = 0;

    _frameAvailable = false;
}

void RawCSIRecorder::begin()
{
    _packetCount = 0;

    _frameAvailable = false;
}

void RawCSIRecorder::record(
    const RawCSIFrame& frame
)
{

    static uint32_t lastTime = millis();
    static uint32_t packetPerSecond = 0;

    packetPerSecond++;

    if (millis() - lastTime >= 1000)
    {
        Serial.print("CSI Packet/sec : ");
        Serial.println(packetPerSecond);

        packetPerSecond = 0;
        lastTime = millis();
    }

    portENTER_CRITICAL(&rawCSIFrameMux);

    //--------------------------------------------------
    // Store Latest Frame
    //--------------------------------------------------

    _latestFrame = frame;

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    _packetCount++;

    _frameAvailable = true;

    static uint32_t lastPrint = 0;

if (millis() - lastPrint > 1000)
{
    Serial.print("Raw CSI Packets : ");
    Serial.println(_packetCount);

    lastPrint = millis();
}

    portEXIT_CRITICAL(&rawCSIFrameMux);
}

RawCSIFrame
RawCSIRecorder::latestFrame() const
{
    portENTER_CRITICAL(&rawCSIFrameMux);

    RawCSIFrame snapshot = _latestFrame;

    portEXIT_CRITICAL(&rawCSIFrameMux);

    return snapshot;
}

uint64_t
RawCSIRecorder::packetCount() const
{
    portENTER_CRITICAL(&rawCSIFrameMux);

    uint64_t count = _packetCount;

    portEXIT_CRITICAL(&rawCSIFrameMux);

    return count;
}

bool
RawCSIRecorder::hasFrame() const
{
    return _frameAvailable;
}