//
//  FFTTwiddleGenerator.cpp
//  AirSense Firmware
//

#include "FFTTwiddleGenerator.h"

#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTTwiddleGenerator&
FFTTwiddleGenerator::shared()
{
    static FFTTwiddleGenerator instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTTwiddleGenerator::FFTTwiddleGenerator()
{
    reset();
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void FFTTwiddleGenerator::reset()
{
    _fftSize = 0;

    _generated = false;

    for (uint16_t i = 0; i < (MAX_SIZE / 2); i++)
    {
        _cosTable[i] = 0.0f;

        _sinTable[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Generate Twiddle Factors
////////////////////////////////////////////////////////

void FFTTwiddleGenerator::generate(
    uint16_t fftSize
)
{
    //--------------------------------------------------
    // Already Generated
    //--------------------------------------------------

    if (_generated &&
        _fftSize == fftSize)
    {
        return;
    }

    //--------------------------------------------------
    // Invalid Size
    //--------------------------------------------------

    if (fftSize == 0)
    {
        return;
    }

    if (fftSize > MAX_SIZE)
    {
        fftSize = MAX_SIZE;
    }

    _fftSize = fftSize;

    //--------------------------------------------------
    // Generate Lookup Table
    //--------------------------------------------------

    for (uint16_t k = 0;
         k < (fftSize / 2);
         k++)
    {
        float angle =
            (-2.0f *
             PI *
             float(k))
            /
            float(fftSize);

        _cosTable[k] = cosf(angle);

        _sinTable[k] = sinf(angle);
    }

    _generated = true;
}

////////////////////////////////////////////////////////
// Cos Lookup
////////////////////////////////////////////////////////

float FFTTwiddleGenerator::cosine(
    uint16_t index
) const
{
    if (!_generated)
    {
        return 1.0f;
    }

    index %= (_fftSize / 2);

    return _cosTable[index];
}

////////////////////////////////////////////////////////
// Sin Lookup
////////////////////////////////////////////////////////

float FFTTwiddleGenerator::sine(
    uint16_t index
) const
{
    if (!_generated)
    {
        return 0.0f;
    }

    index %= (_fftSize / 2);

    return _sinTable[index];
}

////////////////////////////////////////////////////////
// FFT Size
////////////////////////////////////////////////////////

uint16_t FFTTwiddleGenerator::size() const
{
    return _fftSize;
}