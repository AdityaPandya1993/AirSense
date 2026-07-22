//
//  FrequencyAnalyzerV2.cpp
//  AirSense Firmware
//

#include "FrequencyAnalyzerV2.h"

FrequencyAnalyzerV2&
FrequencyAnalyzerV2::shared()
{
    static FrequencyAnalyzerV2 instance;

    return instance;
}

FrequencyAnalyzerV2::FrequencyAnalyzerV2()
{
    reset();
}

void FrequencyAnalyzerV2::reset()
{
    _heartFrequency = 0.0f;
    _heartBPM = 0.0f;

    _breathingFrequency = 0.0f;
    _breathingRPM = 0.0f;

    _confidence = 0.0f;
}

////////////////////////////////////////////////////////

void FrequencyAnalyzerV2::analyze(
    const float* spectrum,
    uint16_t fftSize,
    float sampleRate
)
{
    if (spectrum == nullptr)
    {
        return;
    }

    float resolution =
        sampleRate /
        float(fftSize);

    analyzeHeartBand(
        spectrum,
        fftSize,
        resolution
    );

    analyzeBreathingBand(
        spectrum,
        fftSize,
        resolution
    );

    //--------------------------------------------------
    // Temporary Confidence
    //--------------------------------------------------

    _confidence = 1.0f;
}

////////////////////////////////////////////////////////

void FrequencyAnalyzerV2::analyzeHeartBand(
    const float* spectrum,
    uint16_t fftSize,
    float resolution
)
{
    float maxValue = 0.0f;

    //--------------------------------------------------
    // 0.8Hz → 2.5Hz
    //--------------------------------------------------

    uint16_t start =
        uint16_t(0.8f / resolution);

    uint16_t end =
        uint16_t(2.5f / resolution);

    for (uint16_t i = start;
         i <= end && i < fftSize / 2;
         i++)
    {
        if (spectrum[i] > maxValue)
        {
            maxValue = spectrum[i];

            _heartFrequency =
                i * resolution;
        }
    }

    _heartBPM =
        _heartFrequency *
        60.0f;
}

////////////////////////////////////////////////////////

void FrequencyAnalyzerV2::analyzeBreathingBand(
    const float* spectrum,
    uint16_t fftSize,
    float resolution
)
{
    float maxValue = 0.0f;

    //--------------------------------------------------
    // 0.10Hz → 0.60Hz
    //--------------------------------------------------

    uint16_t start =
        uint16_t(0.10f / resolution);

    uint16_t end =
        uint16_t(0.60f / resolution);

    for (uint16_t i = start;
         i <= end && i < fftSize / 2;
         i++)
    {
        if (spectrum[i] > maxValue)
        {
            maxValue = spectrum[i];

            _breathingFrequency =
                i * resolution;
        }
    }

    _breathingRPM =
        _breathingFrequency *
        60.0f;
}

////////////////////////////////////////////////////////

float FrequencyAnalyzerV2::heartFrequency() const
{
    return _heartFrequency;
}

float FrequencyAnalyzerV2::heartBPM() const
{
    return _heartBPM;
}

float FrequencyAnalyzerV2::breathingFrequency() const
{
    return _breathingFrequency;
}

float FrequencyAnalyzerV2::breathingRPM() const
{
    return _breathingRPM;
}

float FrequencyAnalyzerV2::confidence() const
{
    return _confidence;
}