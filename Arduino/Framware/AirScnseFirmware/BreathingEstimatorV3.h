//
//  BreathingEstimatorV3.h
//  AirSense Firmware
//

#ifndef BREATHING_ESTIMATOR_V3_H
#define BREATHING_ESTIMATOR_V3_H

#include <Arduino.h>

class BreathingEstimatorV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static BreathingEstimatorV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Process
    //--------------------------------------------------

    void process(
        float dominantFrequency
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float breathingRate() const;

    bool valid() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    BreathingEstimatorV3();

private:

    bool _ready;

    bool _valid;

    float _breathingRate;
};

#endif