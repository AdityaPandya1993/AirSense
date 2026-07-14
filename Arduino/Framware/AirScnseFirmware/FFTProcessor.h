//
//  FFTProcessor.h
//  AirSense Firmware
//

#ifndef FFT_PROCESSOR_H
#define FFT_PROCESSOR_H

#include "DSPConstants.h"

class FFTProcessor
{
public:

    static FFTProcessor& shared();

    void compute(
        const float* samples,
        int count
    );

    float magnitude(
        int index
    ) const;

private:

    FFTProcessor();

    float _magnitude[DSP::FFTSize];
};

#endif