//
//  FFTFrequency.cpp
//  AirSense Firmware
//

#include "FFTFrequency.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTFrequency&
FFTFrequency::shared()
{
    static FFTFrequency instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTFrequency::FFTFrequency()
{
    reset();
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void FFTFrequency::reset()
{
    _frequencyHz = 0.0f;

    _frequencyRPM = 0.0f;

    _frequencyBPM = 0.0f;

    _resolutionHz = 0.0f;
}

////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////

void FFTFrequency::update(
    uint16_t peakIndex,
    uint16_t fftSize,
    float sampleRate
)
{
    if (fftSize == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Frequency Resolution
    //--------------------------------------------------

    _resolutionHz =
        sampleRate /
        float(fftSize);

    //--------------------------------------------------
    // Dominant Frequency
    //--------------------------------------------------

    _frequencyHz =
        float(peakIndex) *
        _resolutionHz;

    //--------------------------------------------------
    // RPM
    //--------------------------------------------------

    _frequencyRPM =
        _frequencyHz *
        60.0f;

    //--------------------------------------------------
    // BPM
    //--------------------------------------------------

    _frequencyBPM =
        _frequencyHz *
        60.0f;
}

////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////

float FFTFrequency::frequencyHz() const
{
    return _frequencyHz;
}

float FFTFrequency::frequencyRPM() const
{
    return _frequencyRPM;
}

float FFTFrequency::frequencyBPM() const
{
    return _frequencyBPM;
}

float FFTFrequency::resolutionHz() const
{
    return _resolutionHz;
}