//
//  SignalBuffer.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2
//
//  Created by Aditya Pandya
//

#ifndef SIGNAL_BUFFER_H
#define SIGNAL_BUFFER_H

#include <Arduino.h>

class SignalBuffer
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static SignalBuffer& shared();

    //--------------------------------------------------
    // Store Signal
    //--------------------------------------------------

    void update(
        const float* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Access Signal
    //--------------------------------------------------

    const float* samples() const;

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t sampleCount() const;

    //--------------------------------------------------
    // Individual Sample
    //--------------------------------------------------

    float sample(
        uint16_t index
    ) const;

private:

    SignalBuffer();

    //--------------------------------------------------
    // Maximum Samples
    //--------------------------------------------------

    static constexpr uint16_t MAX_SAMPLES = 256;

    //--------------------------------------------------
    // Sample Buffer
    //--------------------------------------------------

    float _samples[MAX_SAMPLES];

    //--------------------------------------------------
    // Sample Count
    //--------------------------------------------------

    uint16_t _count;
};

#endif