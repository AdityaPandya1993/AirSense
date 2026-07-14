//
//  FFTProcessor.cpp
//  AirSense Firmware
//

#include "FFTProcessor.h"
#include "DSPConstants.h"

#include <math.h>

FFTProcessor&
FFTProcessor::shared()
{
    static FFTProcessor fft;

    return fft;
}

FFTProcessor::FFTProcessor()
{
    for (int i = 0; i < DSP::FFTSize; i++)
    {
        _magnitude[i] = 0.0f;
    }
}

void FFTProcessor::compute(
    const float* samples,
    int count
)
{
    if (samples == nullptr)
    {
        return;
    }

    for (int k = 0; k < count; k++)
    {
        float real = 0.0f;
        float imag = 0.0f;

        for (int n = 0; n < count; n++)
        {
            float angle =
                (DSP::kTwoPi *
                 float(k) *
                 float(n))
                /
                float(count);

            real +=
                samples[n] *
                cosf(angle);

            imag -=
                samples[n] *
                sinf(angle);
        }

        _magnitude[k] =
            sqrtf(
                real * real +
                imag * imag
            );
    }
}

float FFTProcessor::magnitude(
    int index
) const
{
    if (index < 0 || index >= DSP::FFTSize)
    {
        return 0.0f;
    }

    return _magnitude[index];
}