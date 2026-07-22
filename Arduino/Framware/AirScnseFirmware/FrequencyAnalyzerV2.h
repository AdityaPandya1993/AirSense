//
//  FrequencyAnalyzerV2.h
//  AirSense Firmware
//

#ifndef FREQUENCY_ANALYZER_V2_H
#define FREQUENCY_ANALYZER_V2_H

#include <Arduino.h>

class FrequencyAnalyzerV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FrequencyAnalyzerV2& shared();

    //--------------------------------------------------
    // Analyze
    //--------------------------------------------------

    void analyze(
        const float* spectrum,
        uint16_t fftSize,
        float sampleRate
    );

    //--------------------------------------------------
    // Heart
    //--------------------------------------------------

    float heartFrequency() const;

    float heartBPM() const;

    //--------------------------------------------------
    // Breathing
    //--------------------------------------------------

    float breathingFrequency() const;

    float breathingRPM() const;

    //--------------------------------------------------
    // Confidence
    //--------------------------------------------------

    float confidence() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FrequencyAnalyzerV2();

    void analyzeHeartBand(
        const float* spectrum,
        uint16_t fftSize,
        float resolution
    );

    void analyzeBreathingBand(
        const float* spectrum,
        uint16_t fftSize,
        float resolution
    );

private:

    float _heartFrequency;
    float _heartBPM;

    float _breathingFrequency;
    float _breathingRPM;

    float _confidence;
};

#endif