//
//  RawCSIRecorder.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "RawCSIRecorder.h"

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
    //--------------------------------------------------
    // Store Latest Frame
    //--------------------------------------------------

    _latestFrame = frame;

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    _packetCount++;

    _frameAvailable = true;
}

const RawCSIFrame&
RawCSIRecorder::latestFrame() const
{
    return _latestFrame;
}

uint64_t
RawCSIRecorder::packetCount() const
{
    return _packetCount;
}

bool
RawCSIRecorder::hasFrame() const
{
    return _frameAvailable;
}