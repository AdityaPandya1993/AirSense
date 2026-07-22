//
//  FFTMagnitude.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.3
//

#include "FFTMagnitude.h"

#include <math.h>

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTMagnitude&
FFTMagnitude::shared()
{
    static FFTMagnitude instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTMagnitude::FFTMagnitude()
{
    reset();
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void FFTMagnitude::reset()
{
    _fftSize = 0;

    for (uint16_t i = 0; i < MAX_SIZE; i++)
    {
        _magnitude[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Compute Magnitude Spectrum
////////////////////////////////////////////////////////

void FFTMagnitude::compute(
    const float* real,
    const float* imag,
    uint16_t fftSize
)
{
    if (real == nullptr ||
        imag == nullptr)
    {
        return;
    }

    if (fftSize > MAX_SIZE)
    {
        fftSize = MAX_SIZE;
    }

    _fftSize = fftSize;

    //--------------------------------------------------
    // Magnitude
    //--------------------------------------------------

    for (uint16_t i = 0; i < fftSize; i++)
    {
        float re = real[i];

        float im = imag[i];

        _magnitude[i] =
            sqrtf(
                (re * re) +
                (im * im)
            );
    }
}

////////////////////////////////////////////////////////
// Get Magnitude
////////////////////////////////////////////////////////

float FFTMagnitude::magnitude(
    uint16_t index
) const
{
    if (index >= _fftSize)
    {
        return 0.0f;
    }

    return _magnitude[index];
}

////////////////////////////////////////////////////////
// Spectrum Pointer
////////////////////////////////////////////////////////

const float*
FFTMagnitude::spectrum() const
{
    return _magnitude;
}

////////////////////////////////////////////////////////
// FFT Size
////////////////////////////////////////////////////////

uint16_t FFTMagnitude::size() const
{
    return _fftSize;
}