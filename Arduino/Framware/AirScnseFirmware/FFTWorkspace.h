//
//  FFTWorkspace.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#ifndef FFT_WORKSPACE_H
#define FFT_WORKSPACE_H

#include <Arduino.h>

class FFTWorkspace
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTWorkspace& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

    //--------------------------------------------------
    // Buffers
    //--------------------------------------------------

    float* real();

    float* imag();

    float* magnitude();

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t capacity() const;

    bool ready() const;

private:

    FFTWorkspace();

    bool _ready;
};

#endif