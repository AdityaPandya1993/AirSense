//
//  MotionEnergy.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "MotionEnergy.h"

#include <math.h>

MotionEnergy&
MotionEnergy::shared()
{
    static MotionEnergy instance;

    return instance;
}

MotionEnergy::MotionEnergy()
{
    _count = 0;

    _energy = 0.0f;

    //--------------------------------------------------
    // Clear Previous Packet
    //--------------------------------------------------

    for (uint16_t i = 0; i < MAX_SAMPLES; i++)
    {
        _previous[i] = 0.0f;
    }
}

float MotionEnergy::energy() const
{
    return _energy;
}

uint16_t MotionEnergy::sampleCount() const
{
    return _count;
}

void MotionEnergy::calculate(
    const FilteredSample* samples,
    uint16_t count
)
{
    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    _energy = 0.0f;

    _count = count;

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // First Packet
    //--------------------------------------------------

    static bool firstPacket = true;

    if (firstPacket)
    {
        for (uint16_t i = 0; i < count; i++)
        {
            _previous[i] = samples[i].amplitude;
        }

        firstPacket = false;

        return;
    }

        //--------------------------------------------------
    // Calculate Motion Energy
    //--------------------------------------------------

    float sum = 0.0f;

    for (uint16_t i = 0; i < count; i++)
    {
        //--------------------------------------------------
        // Difference
        //--------------------------------------------------

        float difference =
            samples[i].amplitude - _previous[i];

        //--------------------------------------------------
        // Absolute Difference
        //--------------------------------------------------

        sum += fabsf(difference);

        //--------------------------------------------------
        // Save Current Packet
        //--------------------------------------------------

        _previous[i] = samples[i].amplitude;
    }

    //--------------------------------------------------
    // Average Energy
    //--------------------------------------------------

    _energy = sum / count;
}