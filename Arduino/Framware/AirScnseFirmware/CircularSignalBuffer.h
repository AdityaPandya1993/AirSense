//
//  CircularSignalBuffer.h
//  AirSense Firmware
//
//  DSP V4
//

#ifndef CIRCULAR_SIGNAL_BUFFER_H
#define CIRCULAR_SIGNAL_BUFFER_H

#include <Arduino.h>
#include "DSPConfig.h"

class CircularSignalBuffer
{
public:

    static CircularSignalBuffer& shared();

    void begin();

    void reset();

    //--------------------------------------------------
    // Add Samples
    //--------------------------------------------------

    void push(
        const float* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Ready
    //--------------------------------------------------

    bool ready() const;

    //--------------------------------------------------
    // Read Buffer
    //--------------------------------------------------

    const float* data();

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    uint16_t size() const;

    uint32_t totalSamples() const;

private:

    CircularSignalBuffer();

private:

    float _buffer[DSPConfig::FFT_SIZE];

    float _linearBuffer[DSPConfig::FFT_SIZE];

    uint16_t _writeIndex;

    bool _filled;

    uint32_t _totalSamples;
};

#endif