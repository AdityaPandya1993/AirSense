//
//  FFTButterflyV3.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//
//  Created by Aditya Pandya
//

#ifndef FFT_BUTTERFLY_V3_H
#define FFT_BUTTERFLY_V3_H

#include <Arduino.h>

class FFTButterflyV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTButterflyV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Execute FFT
    //--------------------------------------------------

    void process(
        float* real,
        float* imag,
        uint16_t count
    );

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FFTButterflyV3();

    //--------------------------------------------------
    // Internal Stages
    //--------------------------------------------------

    void bitReverse(
        float* real,
        float* imag,
        uint16_t count
    );

    void butterfly(
        float* real,
        float* imag,
        uint16_t count
    );

    //--------------------------------------------------
    // Utilities
    //--------------------------------------------------

    uint16_t reverseBits(
        uint16_t value,
        uint8_t bits
    ) const;

private:

    bool _ready;
};

#endif