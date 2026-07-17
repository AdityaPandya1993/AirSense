//
//  CSISample.h
//  AirSense Firmware
//

#ifndef CSI_SAMPLE_H
#define CSI_SAMPLE_H

#include <Arduino.h>

struct CSISample
{
    //--------------------------------------------------
    // Subcarrier Index
    //--------------------------------------------------

    uint16_t index;

    //--------------------------------------------------
    // Signal Magnitude
    //--------------------------------------------------

    float amplitude;

    //--------------------------------------------------
    // Signal Phase
    //--------------------------------------------------

    float phase;
};

#endif