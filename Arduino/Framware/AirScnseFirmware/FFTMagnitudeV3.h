//
//  FFTMagnitudeV3.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#ifndef FFT_MAGNITUDE_V3_H
#define FFT_MAGNITUDE_V3_H

#include <Arduino.h>

class FFTMagnitudeV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTMagnitudeV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Execute
    //--------------------------------------------------

    void process(
        const float* real,
        const float* imag,
        float* magnitude,
        uint16_t count
    );

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FFTMagnitudeV3();

    bool _ready;
};

#endif