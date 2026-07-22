//
//  HeartRateEstimatorV3.h
//  AirSense Firmware
//

#ifndef HEART_RATE_ESTIMATOR_V3_H
#define HEART_RATE_ESTIMATOR_V3_H

#include <Arduino.h>

class HeartRateEstimatorV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static HeartRateEstimatorV3& shared();

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

    float bpm() const;

    bool valid() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    HeartRateEstimatorV3();

private:

    bool _ready;

    bool _valid;

    float _bpm;
};

#endif