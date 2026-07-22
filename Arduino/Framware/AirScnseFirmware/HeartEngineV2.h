//
//  HeartEngineV2.h
//  AirSense Firmware
//

#ifndef HEART_ENGINE_V2_H
#define HEART_ENGINE_V2_H

#include <Arduino.h>

class HeartEngineV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static HeartEngineV2& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update(
        float heartBPM,
        float confidence
    );

    //--------------------------------------------------
    // Output
    //--------------------------------------------------

    float currentBPM() const;

    float filteredBPM() const;

    float confidence() const;

    bool isValid() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    HeartEngineV2();

    void movingAverage(
        float bpm
    );

private:

    static constexpr uint8_t FILTER_SIZE = 8;

    float _history[FILTER_SIZE];

    uint8_t _index;

    float _currentBPM;

    float _filteredBPM;

    float _confidence;

    bool _valid;
};

#endif