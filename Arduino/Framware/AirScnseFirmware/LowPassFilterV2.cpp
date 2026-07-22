//
//  LowPassFilterV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//

#include "LowPassFilterV2.h"
#include "SignalBufferV2.h"

LowPassFilterV2&
LowPassFilterV2::shared()
{
    static LowPassFilterV2 filter;

    return filter;
}

LowPassFilterV2::LowPassFilterV2()
{
    reset();
}

void LowPassFilterV2::reset()
{
    _previousOutput = 0.0f;
}

void LowPassFilterV2::process()
{
    float* samples =
        SignalBufferV2::shared().workingSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // First Sample
    //--------------------------------------------------

    _previousOutput = samples[0];

    //--------------------------------------------------
    // Low Pass Filtering
    //--------------------------------------------------

    for (uint16_t i = 1; i < count; i++)
    {
        _previousOutput =
            _previousOutput +
            ALPHA *
            (
                samples[i] -
                _previousOutput
            );

        samples[i] = _previousOutput;
    }
}