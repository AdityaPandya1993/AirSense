//
//  SignalBufferV3.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//
//  Created by Aditya Pandya
//

#ifndef SIGNAL_BUFFER_V3_H
#define SIGNAL_BUFFER_V3_H

#include <Arduino.h>

class SignalBufferV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static SignalBufferV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

    //--------------------------------------------------
    // Update Samples
    //--------------------------------------------------

    void update(
        const float* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Buffer
    //--------------------------------------------------

    float* samples();

    const float* samples() const;

    //--------------------------------------------------
    // Individual Sample
    //--------------------------------------------------

    float sample(
        uint16_t index
    ) const;

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t sampleCount() const;

    uint16_t capacity() const;

    bool isReady() const;

private:

    SignalBufferV3();

private:

    static constexpr uint16_t MAX_SAMPLES = 256;

    uint16_t _sampleCount;

    bool _ready;
};

#endif