//
//  SignalBuffer.h
//  AirSense Firmware
//
//  DSP V4.1
//

#ifndef SIGNAL_BUFFER_H
#define SIGNAL_BUFFER_H

#include <Arduino.h>
#include "DSPConfig.h"

class SignalBuffer
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static SignalBuffer& shared();

    //--------------------------------------------------
    // Update Raw Signal
    //--------------------------------------------------

    void update(
        const float* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Copy Operations
    //--------------------------------------------------

    void copyRawToWorking();

    void copyWorkingToFFT();

    //--------------------------------------------------
    // Buffers
    //--------------------------------------------------

    const float* rawSamples() const;

    float* workingSamples();

    float* fftSamples();

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t sampleCount() const;

    uint16_t capacity() const;

    const float* samples() const;

    //--------------------------------------------------
    // Utility
    //--------------------------------------------------

    void clear();

private:

    SignalBuffer();

private:

    //--------------------------------------------------
    // Buffers
    //--------------------------------------------------

    float _raw[DSPConfig::FFT_SIZE];

    float _working[DSPConfig::FFT_SIZE];

    float _fft[DSPConfig::FFT_SIZE];

    //--------------------------------------------------
    // Sample Count
    //--------------------------------------------------

    uint16_t _count;
};

#endif