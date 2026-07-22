//
//  BandPassFilter.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2
//

#ifndef BAND_PASS_FILTER_H
#define BAND_PASS_FILTER_H

#include <Arduino.h>

class BandPassFilter
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static BandPassFilter& shared();

    //--------------------------------------------------
    // Process Shared Signal Buffer
    //--------------------------------------------------

    void process();

private:

    BandPassFilter();

    //--------------------------------------------------
    // Filter State
    //--------------------------------------------------

    float _hpPreviousInput;

    float _hpPreviousOutput;

    float _lpPreviousOutput;

    //--------------------------------------------------
    // Filter Coefficients
    //--------------------------------------------------

    static constexpr float HP_ALPHA = 0.95f;

    static constexpr float LP_ALPHA = 0.20f;

    //--------------------------------------------------
    // Temporary Working Buffer
    //--------------------------------------------------

    static constexpr uint16_t MAX_SAMPLES = 256;

    float _filtered[MAX_SAMPLES];
};

#endif