//
//  ConfidenceEngineV2.h
//  AirSense Firmware
//

#ifndef CONFIDENCE_ENGINE_V2_H
#define CONFIDENCE_ENGINE_V2_H

#include <Arduino.h>

class ConfidenceEngineV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static ConfidenceEngineV2& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update(
        float fftPeak,
        float noiseFloor,
        float heartConfidence,
        float breathingConfidence,
        float signalQuality,
        bool motionDetected
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float confidence() const;

    uint8_t confidencePercent() const;

    bool isReliable() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    ConfidenceEngineV2();

private:

    float _confidence;

    uint8_t _confidencePercent;

    bool _reliable;
};

#endif