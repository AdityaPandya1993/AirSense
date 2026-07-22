//
//  SignalBufferV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//
//  Created by Aditya Pandya
//

#ifndef SIGNAL_BUFFER_V2_H
#define SIGNAL_BUFFER_V2_H

#include <Arduino.h>

class SignalBufferV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static SignalBufferV2& shared();

    //--------------------------------------------------
    // Raw Buffer
    //--------------------------------------------------

    void updateRaw(
        const float* samples,
        uint16_t count
    );

    const float* rawSamples() const;

    //--------------------------------------------------
    // Working Buffer
    //--------------------------------------------------

    float* workingSamples();

    const float* workingSamples() const;

    //--------------------------------------------------
    // FFT Input Buffer
    //--------------------------------------------------

    float* fftSamples();

    const float* fftSamples() const;

    //--------------------------------------------------
    // Spectrum Buffer
    //--------------------------------------------------

    float* spectrum();

    const float* spectrum() const;

    //--------------------------------------------------
    // Copy Operations
    //--------------------------------------------------

    void copyRawToWorking();

    void copyWorkingToFFT();

    //--------------------------------------------------
    // Utility
    //--------------------------------------------------

    void clear();

    void reset();

    uint16_t sampleCount() const;

    uint16_t capacity() const;

private:

    SignalBufferV2();

    static constexpr uint16_t MAX_SAMPLES = 256;

    //--------------------------------------------------
    // Buffers
    //--------------------------------------------------

    float _raw[MAX_SAMPLES];

    float _working[MAX_SAMPLES];

    float _fft[MAX_SAMPLES];

    float _spectrum[MAX_SAMPLES];

    //--------------------------------------------------
    // Sample Count
    //--------------------------------------------------

    uint16_t _count;
};

#endif