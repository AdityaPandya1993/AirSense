//
//  IQSample.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef IQ_SAMPLE_H
#define IQ_SAMPLE_H

#include <Arduino.h>

struct IQSample
{
    int8_t i;
    int8_t q;
};

#endif