//
//  SharedDSPWorkspace.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//
//  Created by Aditya Pandya
//

#ifndef SHARED_DSP_WORKSPACE_H
#define SHARED_DSP_WORKSPACE_H

#include <Arduino.h>

class SharedDSPWorkspace
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static SharedDSPWorkspace& shared();

    //--------------------------------------------------
    // Initialization
    //--------------------------------------------------

    bool begin();

    void reset();

    void release();

    //--------------------------------------------------
    // Signal Buffer
    //--------------------------------------------------

    float* signal();

    //--------------------------------------------------
    // FFT Real
    //--------------------------------------------------

    float* fftReal();

    //--------------------------------------------------
    // FFT Imaginary
    //--------------------------------------------------

    float* fftImag();

    //--------------------------------------------------
    // Magnitude
    //--------------------------------------------------

    float* magnitude();

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t capacity() const;

    bool ready() const;

private:

    SharedDSPWorkspace();

private:

    static constexpr uint16_t BUFFER_SIZE = 256;

    bool _ready;

    float* _signal;

    float* _fftReal;

    float* _fftImag;

    float* _magnitude;
};

#endif