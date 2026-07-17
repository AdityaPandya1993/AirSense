//
//  IQDecoder.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "IQDecoder.h"

IQDecoder&
IQDecoder::shared()
{
    static IQDecoder decoder;

    return decoder;
}

IQDecoder::IQDecoder()
{
    _sampleCount = 0;
}

void IQDecoder::decode(
    const RawCSIFrame& frame
)
{
    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    _sampleCount = 0;

    //--------------------------------------------------
    // Evidence Based Payload Offset
    //--------------------------------------------------

    const uint16_t payloadOffset = 12;

    //--------------------------------------------------
    // Safety Check
    //--------------------------------------------------

    if (frame.length <= payloadOffset)
    {
        return;
    }

    //--------------------------------------------------
    // Available Bytes
    //--------------------------------------------------

    uint16_t availableBytes =
        frame.length - payloadOffset;

    //--------------------------------------------------
    // IQ Sample Count
    //--------------------------------------------------

    _sampleCount =
        availableBytes / 2;

    if (_sampleCount > MAX_IQ_SAMPLES)
    {
        _sampleCount = MAX_IQ_SAMPLES;
    }

    //--------------------------------------------------
    // Decode IQ Samples
    //--------------------------------------------------

    uint16_t rawIndex = payloadOffset;

    for (uint16_t i = 0;
         i < _sampleCount;
         i++)
    {
        _samples[i].i =
            frame.data[rawIndex];

        _samples[i].q =
            frame.data[rawIndex + 1];

        rawIndex += 2;
    }
}

const IQSample*
IQDecoder::samples() const
{
    return _samples;
}

uint16_t
IQDecoder::sampleCount() const
{
    return _sampleCount;
}