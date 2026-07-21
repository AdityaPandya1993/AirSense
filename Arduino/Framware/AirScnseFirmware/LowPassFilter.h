//
//  LowPassFilter.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H

#include <Arduino.h>

#include "CenteredSample.h"
#include "FilteredSample.h"

class LowPassFilter
{
public:

    static LowPassFilter& shared();

    void filter(
        const CenteredSample* samples,
        uint16_t count
    );

    const FilteredSample* samples() const;

    uint16_t sampleCount() const;

private:

    LowPassFilter();

    static constexpr uint16_t MAX_SAMPLES = 256;

    //--------------------------------------------------
    // Filter Strength
    //
    // 0.0 = Heavy Smoothing
    // 1.0 = No Filtering
    //--------------------------------------------------

    static constexpr float ALPHA = 0.25f;

    FilteredSample _samples[MAX_SAMPLES];

    uint16_t _count;
};

#endif