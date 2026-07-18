//
//  DCRemoval.h
//  AirSense Firmware
//

#ifndef DC_REMOVAL_H
#define DC_REMOVAL_H

#include <Arduino.h>

#include "CSISample.h"
#include "CenteredSample.h"

class DCRemoval
{
public:

    static DCRemoval& shared();

    void remove(
        const CSISample* samples,
        uint16_t count
    );

    const CenteredSample* samples() const;

    uint16_t sampleCount() const;

    float meanAmplitude() const;

private:

    DCRemoval();

private:

    static const uint16_t MAX_SAMPLES = 256;

    CenteredSample _samples[MAX_SAMPLES];

    uint16_t _count;

    float _meanAmplitude;
};

#endif