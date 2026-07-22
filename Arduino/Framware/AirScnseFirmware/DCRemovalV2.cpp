//
//  DCRemovalV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//

#include "DCRemovalV2.h"
#include "SignalBufferV2.h"

DCRemovalV2&
DCRemovalV2::shared()
{
    static DCRemovalV2 instance;

    return instance;
}

DCRemovalV2::DCRemovalV2()
{
    _mean = 0.0f;
}

void DCRemovalV2::process()
{
    float* samples =
        SignalBufferV2::shared().workingSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        _mean = 0.0f;
        return;
    }

    //--------------------------------------------------
    // Calculate Mean
    //--------------------------------------------------

    float sum = 0.0f;

    for (uint16_t i = 0; i < count; i++)
    {
        sum += samples[i];
    }

    _mean = sum / count;

    //--------------------------------------------------
    // Remove DC Offset
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        samples[i] -= _mean;
    }
}

float
DCRemovalV2::mean() const
{
    return _mean;
}