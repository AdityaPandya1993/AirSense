//
//  FrequencyAnalyzer.cpp
//  AirSense Firmware
//

#include "FrequencyAnalyzer.h"

FrequencyAnalyzer&
FrequencyAnalyzer::shared()
{
    static FrequencyAnalyzer analyzer;

    return analyzer;
}

FrequencyAnalyzer::FrequencyAnalyzer()
{

}

float FrequencyAnalyzer::peakFrequency(
    int peakIndex,
    int fftSize,
    float sampleRate
)
{
    if (fftSize <= 0)
    {
        return 0.0f;
    }

    return
        (float(peakIndex) * sampleRate)
        /
        float(fftSize);
}

float FrequencyAnalyzer::frequencyToBPM(
    float frequency
)
{
    return frequency * 60.0f;
}