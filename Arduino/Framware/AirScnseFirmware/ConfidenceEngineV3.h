//
//  ConfidenceEngineV3.h
//  AirSense Firmware
//

#ifndef CONFIDENCE_ENGINE_V3_H
#define CONFIDENCE_ENGINE_V3_H

#include <Arduino.h>

class ConfidenceEngineV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static ConfidenceEngineV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Process
    //--------------------------------------------------

    void process(
        bool heartValid,
        bool breathingValid,
        float peakMagnitude
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float confidence() const;

    bool detected() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    ConfidenceEngineV3();

private:

    bool _ready;

    bool _detected;

    float _confidence;
};

#endif