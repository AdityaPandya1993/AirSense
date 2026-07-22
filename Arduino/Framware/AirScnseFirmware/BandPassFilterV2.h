//
//  BandPassFilterV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//
//  Created by Aditya Pandya
//

#ifndef BAND_PASS_FILTER_V2_H
#define BAND_PASS_FILTER_V2_H

#include <Arduino.h>

class BandPassFilterV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static BandPassFilterV2& shared();

    //--------------------------------------------------
    // Process Working Buffer
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Reset Filter State
    //--------------------------------------------------

    void reset();

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    void printDebug() const;

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    float highPassAlpha() const;

    float lowPassAlpha() const;

private:

    BandPassFilterV2();

    //--------------------------------------------------
    // Previous Filter States
    //--------------------------------------------------

    float _previousInput;

    float _previousHighPass;

    float _previousLowPass;
};

#endif