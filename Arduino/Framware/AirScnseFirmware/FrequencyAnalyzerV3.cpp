//
//  FrequencyAnalyzerV3.cpp
//  AirSense Firmware
//

#include "FrequencyAnalyzerV3.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FrequencyAnalyzerV3&
FrequencyAnalyzerV3::shared()
{
    static FrequencyAnalyzerV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FrequencyAnalyzerV3::FrequencyAnalyzerV3()
{
    reset();
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool FrequencyAnalyzerV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void FrequencyAnalyzerV3::reset()
{
    _ready = false;

    _dominantBin = 0;

    _dominantFrequency = 0.0f;

    _frequencyResolution = 0.0f;

    _peakMagnitude = 0.0f;
}

////////////////////////////////////////////////////////
// Analyze
////////////////////////////////////////////////////////

void FrequencyAnalyzerV3::process(
    uint16_t peakIndex,
    float peakMagnitude,
    uint16_t fftSize,
    float sampleRate
)
{
    if (!_ready)
    {
        return;
    }

    //--------------------------------------------------
    // Frequency Resolution
    //--------------------------------------------------

    _frequencyResolution =
        sampleRate /
        float(fftSize);

    //--------------------------------------------------
    // Peak
    //--------------------------------------------------

    _dominantBin =
        peakIndex;

    _peakMagnitude =
        peakMagnitude;

    //--------------------------------------------------
    // Frequency
    //--------------------------------------------------

    _dominantFrequency =
        float(peakIndex) *
        _frequencyResolution;
}

////////////////////////////////////////////////////////
// Frequency
////////////////////////////////////////////////////////

float
FrequencyAnalyzerV3::dominantFrequency() const
{
    return _dominantFrequency;
}

////////////////////////////////////////////////////////
// Resolution
////////////////////////////////////////////////////////

float
FrequencyAnalyzerV3::frequencyResolution() const
{
    return _frequencyResolution;
}

////////////////////////////////////////////////////////
// Bin
////////////////////////////////////////////////////////

uint16_t
FrequencyAnalyzerV3::dominantBin() const
{
    return _dominantBin;
}

////////////////////////////////////////////////////////
// Magnitude
////////////////////////////////////////////////////////

float
FrequencyAnalyzerV3::peakMagnitude() const
{
    return _peakMagnitude;
}