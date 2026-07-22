//
//  ConfidenceEngineV3.cpp
//  AirSense Firmware
//

#include "ConfidenceEngineV3.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

ConfidenceEngineV3&
ConfidenceEngineV3::shared()
{
    static ConfidenceEngineV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

ConfidenceEngineV3::ConfidenceEngineV3()
{
    reset();
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool ConfidenceEngineV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void ConfidenceEngineV3::reset()
{
    _ready = false;

    _detected = false;

    _confidence = 0.0f;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void ConfidenceEngineV3::process(
    bool heartValid,
    bool breathingValid,
    float peakMagnitude
)
{
    if (!_ready)
    {
        return;
    }

    float score = 0.0f;

    //--------------------------------------------------
    // Heart Signal
    //--------------------------------------------------

    if (heartValid)
    {
        score += 40.0f;
    }

    //--------------------------------------------------
    // Breathing Signal
    //--------------------------------------------------

    if (breathingValid)
    {
        score += 40.0f;
    }

    //--------------------------------------------------
    // FFT Peak Strength
    //--------------------------------------------------

    if (peakMagnitude > 1.0f)
    {
        score += 20.0f;
    }

    //--------------------------------------------------
    // Clamp
    //--------------------------------------------------

    if (score > 100.0f)
    {
        score = 100.0f;
    }

    _confidence = score;

    _detected = (_confidence >= 60.0f);
}

////////////////////////////////////////////////////////
// Confidence
////////////////////////////////////////////////////////

float
ConfidenceEngineV3::confidence() const
{
    return _confidence;
}

////////////////////////////////////////////////////////
// Detection
////////////////////////////////////////////////////////

bool
ConfidenceEngineV3::detected() const
{
    return _detected;
}