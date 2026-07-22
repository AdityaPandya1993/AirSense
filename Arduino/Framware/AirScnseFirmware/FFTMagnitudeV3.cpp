//
//  FFTMagnitudeV3.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "FFTMagnitudeV3.h"

#include <math.h>

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTMagnitudeV3& FFTMagnitudeV3::shared()
{
    static FFTMagnitudeV3 instance;
    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTMagnitudeV3::FFTMagnitudeV3()
{
    _ready = false;
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool FFTMagnitudeV3::begin()
{
    _ready = true;
    return true;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void FFTMagnitudeV3::process(
    const float* real,
    const float* imag,
    float* magnitude,
    uint16_t count
)
{
    //--------------------------------------------------
    // Validation
    //--------------------------------------------------

    if (!_ready)
    {
        return;
    }

    if (real == nullptr)
    {
        return;
    }

    if (imag == nullptr)
    {
        return;
    }

    if (magnitude == nullptr)
    {
        return;
    }

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Magnitude Calculation
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        float r  = real[i];
        float im = imag[i];

        magnitude[i] = sqrtf((r * r) + (im * im));
    }
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void FFTMagnitudeV3::reset()
{
    _ready = false;
}