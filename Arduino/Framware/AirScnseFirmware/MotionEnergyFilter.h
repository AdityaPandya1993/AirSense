//
//  MotionEnergyFilter.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef MOTION_ENERGY_FILTER_H
#define MOTION_ENERGY_FILTER_H

#include <Arduino.h>

class MotionEnergyFilter
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static MotionEnergyFilter& shared();

    //--------------------------------------------------
    // Filter Motion Energy
    //--------------------------------------------------

    void filter(
        float energy
    );

    //--------------------------------------------------
    // Filtered Energy
    //--------------------------------------------------

    float energy() const;

private:

    MotionEnergyFilter();

    //--------------------------------------------------
    // Exponential Moving Average
    //
    // 0.0 = Heavy Smoothing
    // 1.0 = No Filtering
    //--------------------------------------------------

    static constexpr float ALPHA = 0.20f;

    //--------------------------------------------------
    // Current Filtered Energy
    //--------------------------------------------------

    float _energy;

    //--------------------------------------------------
    // First Packet Flag
    //--------------------------------------------------

    bool _firstPacket;
};

#endif