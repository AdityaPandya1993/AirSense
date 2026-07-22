//
//  BreathingEstimatorV3.cpp
//  AirSense Firmware
//

#include "BreathingEstimatorV3.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

BreathingEstimatorV3&
BreathingEstimatorV3::shared()
{
    static BreathingEstimatorV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

BreathingEstimatorV3::BreathingEstimatorV3()
{
    reset();
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool BreathingEstimatorV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void BreathingEstimatorV3::reset()
{
    _ready = false;

    _valid = false;

    _breathingRate = 0.0f;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void BreathingEstimatorV3::process(
    float dominantFrequency
)
{
    if (!_ready)
    {
        return;
    }

    //--------------------------------------------------
    // Frequency -> Breaths Per Minute
    //--------------------------------------------------

    float bpm =
        dominantFrequency * 60.0f;

    //--------------------------------------------------
    // Human Breathing Range
    //--------------------------------------------------

    if (
        bpm >= 6.0f &&
        bpm <= 40.0f
    )
    {
        _valid = true;

        _breathingRate = bpm;
    }
    else
    {
        _valid = false;

        _breathingRate = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Breathing Rate
////////////////////////////////////////////////////////

float
BreathingEstimatorV3::breathingRate() const
{
    return _breathingRate;
}

////////////////////////////////////////////////////////
// Valid
////////////////////////////////////////////////////////

bool
BreathingEstimatorV3::valid() const
{
    return _valid;
}