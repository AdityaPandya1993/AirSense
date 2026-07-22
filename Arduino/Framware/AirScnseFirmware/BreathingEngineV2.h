//
//  BreathingEngineV2.h
//  AirSense Firmware
//

#ifndef BREATHING_ENGINE_V2_H
#define BREATHING_ENGINE_V2_H

#include <Arduino.h>

class BreathingEngineV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static BreathingEngineV2& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update(
        float respirationRPM,
        float confidence
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float currentRPM() const;

    float filteredRPM() const;

    float confidence() const;

    bool isValid() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    BreathingEngineV2();

    void movingAverage(
        float rpm
    );

private:

    static constexpr uint8_t FILTER_SIZE = 8;

    float _history[FILTER_SIZE];

    uint8_t _index;

    float _currentRPM;

    float _filteredRPM;

    float _confidence;

    bool _valid;
};

#endif