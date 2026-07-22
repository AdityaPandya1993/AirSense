//
//  LowPassFilterV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//

#ifndef LOW_PASS_FILTER_V2_H
#define LOW_PASS_FILTER_V2_H

#include <Arduino.h>

class LowPassFilterV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static LowPassFilterV2& shared();

    //--------------------------------------------------
    // Process Working Buffer
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Reset Filter
    //--------------------------------------------------

    void reset();

private:

    LowPassFilterV2();

    //--------------------------------------------------
    // Low Pass Alpha
    //--------------------------------------------------

    static constexpr float ALPHA = 0.25f;

    //--------------------------------------------------
    // Previous Output
    //--------------------------------------------------

    float _previousOutput;
};

#endif