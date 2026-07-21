//
//  FilteredSample.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef FILTERED_SAMPLE_H
#define FILTERED_SAMPLE_H

#include <Arduino.h>

struct FilteredSample
{
    //--------------------------------------------------
    // Sample Index
    //--------------------------------------------------

    uint16_t index;

    //--------------------------------------------------
    // Filtered Amplitude
    //--------------------------------------------------

    float amplitude;

    //--------------------------------------------------
    // Phase
    //--------------------------------------------------

    // Phase હાલ unchanged રહેશે.
    // Low Pass Filter માત્ર amplitude પર લાગશે.

    float phase;
};

#endif