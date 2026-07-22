//
//  HeartRateEstimatorV3.cpp
//  AirSense Firmware
//

#include "HeartRateEstimatorV3.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

HeartRateEstimatorV3&
HeartRateEstimatorV3::shared()
{
    static HeartRateEstimatorV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

HeartRateEstimatorV3::HeartRateEstimatorV3()
{
    reset();
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool HeartRateEstimatorV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void HeartRateEstimatorV3::reset()
{
    _ready = false;

    _valid = false;

    _bpm = 0.0f;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void HeartRateEstimatorV3::process(
    float dominantFrequency
)
{
    if (!_ready)
    {
        return;
    }

    //--------------------------------------------------
    // Frequency -> BPM
    //--------------------------------------------------

    float bpm =
        dominantFrequency * 60.0f;

    //--------------------------------------------------
    // Human Heart Range
    //--------------------------------------------------

    if (
        bpm >= 40.0f &&
        bpm <= 180.0f
    )
    {
        _valid = true;

        _bpm = bpm;
    }
    else
    {
        _valid = false;

        _bpm = 0.0f;
    }
}

////////////////////////////////////////////////////////
// BPM
////////////////////////////////////////////////////////

float
HeartRateEstimatorV3::bpm() const
{
    return _bpm;
}

////////////////////////////////////////////////////////
// Valid
////////////////////////////////////////////////////////

bool
HeartRateEstimatorV3::valid() const
{
    return _valid;
}