//
//  FFTMagnitude.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.3
//

#ifndef FFT_MAGNITUDE_H
#define FFT_MAGNITUDE_H

#include <Arduino.h>

class FFTMagnitude
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTMagnitude& shared();

    //--------------------------------------------------
    // Compute Magnitude Spectrum
    //--------------------------------------------------

    void compute(
        const float* real,
        const float* imag,
        uint16_t fftSize
    );

    //--------------------------------------------------
    // Access
    //--------------------------------------------------

    float magnitude(
        uint16_t index
    ) const;

    const float* spectrum() const;

    uint16_t size() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FFTMagnitude();

private:

    static constexpr uint16_t MAX_SIZE = 256;

    float _magnitude[MAX_SIZE];

    uint16_t _fftSize;
};

#endif