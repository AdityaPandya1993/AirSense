//
//  LowPassFilter.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "LowPassFilter.h"

LowPassFilter&
LowPassFilter::shared()
{
    static LowPassFilter filter;

    return filter;
}

LowPassFilter::LowPassFilter()
{
    _count = 0;
}

void LowPassFilter::filter(
    const CenteredSample* samples,
    uint16_t count
)
{
    //--------------------------------------------------
    // Safety
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
    // First Sample
    //
    // First sample cannot be filtered because
    // there is no previous value.
    //--------------------------------------------------

    _samples[0].index = samples[0].index;

    _samples[0].amplitude =
        samples[0].amplitude;

    _samples[0].phase =
        samples[0].phase;

    //--------------------------------------------------
    // Exponential Low Pass Filter
    //--------------------------------------------------

    for (uint16_t i = 1; i < _count; i++)
    {
        _samples[i].index =
            samples[i].index;

        _samples[i].amplitude =
            (ALPHA * samples[i].amplitude)
            +
            ((1.0f - ALPHA) * _samples[i - 1].amplitude);

        //--------------------------------------------------
        // Phase
        //
        // Phase હજુ filter નથી કરવો.
        //--------------------------------------------------

        _samples[i].phase =
            samples[i].phase;
    }
}

const FilteredSample*
LowPassFilter::samples() const
{
    return _samples;
}

uint16_t
LowPassFilter::sampleCount() const
{
    return _count;
}