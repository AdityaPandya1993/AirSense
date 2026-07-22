//
//  MotionEnergy.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef MOTION_ENERGY_H
#define MOTION_ENERGY_H

#include <Arduino.h>

#include "FilteredSample.h"

class MotionEnergy
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static MotionEnergy& shared();

    //--------------------------------------------------
    // Calculate Motion Energy
    //--------------------------------------------------

    void calculate(
        const FilteredSample* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Result
    //--------------------------------------------------

    float energy() const;

    //--------------------------------------------------
    // Sample Count
    //--------------------------------------------------

    uint16_t sampleCount() const;

private:

    MotionEnergy();

    //--------------------------------------------------
    // Maximum CSI Samples
    //--------------------------------------------------

    static constexpr uint16_t MAX_SAMPLES = 256;

    //--------------------------------------------------
    // Previous Packet Amplitude
    //--------------------------------------------------

    float _previous[MAX_SAMPLES];

    //--------------------------------------------------
    // Current Packet Count
    //--------------------------------------------------

    uint16_t _count;

    //--------------------------------------------------
    // Motion Energy
    //--------------------------------------------------

    float _energy;
};

#endif