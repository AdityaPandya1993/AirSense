//
//  MotionEnergyFilter.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "MotionEnergyFilter.h"

MotionEnergyFilter&
MotionEnergyFilter::shared()
{
    static MotionEnergyFilter instance;

    return instance;
}

MotionEnergyFilter::MotionEnergyFilter()
{
    _energy = 0.0f;

    _firstPacket = true;
}

float MotionEnergyFilter::energy() const
{
    return _energy;
}

void MotionEnergyFilter::filter(
    float energy
)
{
    //--------------------------------------------------
    // First Packet
    //--------------------------------------------------

    if (_firstPacket)
    {
        _energy = energy;

        _firstPacket = false;

        return;
    }

        //--------------------------------------------------
    // Exponential Moving Average
    //--------------------------------------------------

    _energy =
        (ALPHA * energy) +
        ((1.0f - ALPHA) * _energy);
}