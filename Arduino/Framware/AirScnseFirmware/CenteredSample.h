//
//  CenteredSample.h
//  AirSense Firmware
//

#ifndef CENTERED_SAMPLE_H
#define CENTERED_SAMPLE_H

#include <Arduino.h>

struct CenteredSample
{
    uint16_t index;

    float amplitude;

    float phase;
};

#endif