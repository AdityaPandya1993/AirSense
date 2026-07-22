//
//  FFTTwiddleTable.cpp
//  AirSense Firmware
//

#include "FFTTwiddleTable.h"

#include <math.h>

FFTTwiddleTable&
FFTTwiddleTable::shared()
{
    static FFTTwiddleTable table;

    return table;
}

FFTTwiddleTable::FFTTwiddleTable()
{
    _initialized = false;
}

void FFTTwiddleTable::initialize(uint16_t fftSize)
{
    if (_initialized)
    {
        return;
    }

    for (uint16_t i = 0; i < fftSize / 2; i++)
    {
        float angle =
            -2.0f *
            PI *
            float(i) /
            float(fftSize);

        _cos[i] = cosf(angle);

        _sin[i] = sinf(angle);
    }

    _initialized = true;
}

float FFTTwiddleTable::cosine(uint16_t index) const
{
    return _cos[index];
}

float FFTTwiddleTable::sine(uint16_t index) const
{
    return _sin[index];
}