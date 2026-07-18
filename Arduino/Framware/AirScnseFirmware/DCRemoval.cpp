//
//  DCRemoval.cpp
//  AirSense Firmware
//

#include "DCRemoval.h"

DCRemoval&
DCRemoval::shared()
{
    static DCRemoval remover;

    return remover;
}

DCRemoval::DCRemoval()
{
    _count = 0;
    _meanAmplitude = 0.0f;
}

void DCRemoval::remove(
    const CSISample* samples,
    uint16_t count
)
{
    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    _count = count;

    if (_count > MAX_SAMPLES)
    {
        _count = MAX_SAMPLES;
    }

    if (_count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Calculate Mean Amplitude
    //--------------------------------------------------

    _meanAmplitude = 0.0f;

    for (uint16_t i = 0; i < _count; i++)
    {
        _meanAmplitude += samples[i].amplitude;
    }

    _meanAmplitude /= _count;

    //--------------------------------------------------
    // Remove DC Component
    //--------------------------------------------------

    for (uint16_t i = 0; i < _count; i++)
    {
        _samples[i].index = samples[i].index;

        _samples[i].amplitude =
            samples[i].amplitude - _meanAmplitude;

        _samples[i].phase =
            samples[i].phase;
    }
}
const CenteredSample*
DCRemoval::samples() const
{
    return _samples;
}

uint16_t
DCRemoval::sampleCount() const
{
    return _count;
}

float
DCRemoval::meanAmplitude() const
{
    return _meanAmplitude;
}