//
//  FrequencyAnalyzerV3.h
//  AirSense Firmware
//

#ifndef FREQUENCY_ANALYZER_V3_H
#define FREQUENCY_ANALYZER_V3_H

#include <Arduino.h>

class FrequencyAnalyzerV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FrequencyAnalyzerV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Analyze
    //--------------------------------------------------

    void process(
        uint16_t peakIndex,
        float peakMagnitude,
        uint16_t fftSize,
        float sampleRate
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float dominantFrequency() const;

    float frequencyResolution() const;

    uint16_t dominantBin() const;

    float peakMagnitude() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FrequencyAnalyzerV3();

private:

    bool _ready;

    uint16_t _dominantBin;

    float _dominantFrequency;

    float _frequencyResolution;

    float _peakMagnitude;
};

#endif