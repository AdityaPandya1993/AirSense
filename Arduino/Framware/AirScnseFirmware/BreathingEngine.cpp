//
//  BreathingEngine.cpp
//  AirSense Firmware
//
//  Version : 2.0
//  Phase   : Professional Firmware
//

#include "BreathingEngine.h"

BreathingEngine&
BreathingEngine::shared()
{
    static BreathingEngine engine;

    return engine;
}

BreathingEngine::BreathingEngine()
{
    _frequency = 0.0f;
    _breathingRate = 0;
}

void BreathingEngine::update(
    float frequency
)
{
    _frequency = frequency;

    _breathingRate =
        (int)(frequency * 60.0f);

    //--------------------------------------------------
    // Clamp
    //--------------------------------------------------

    if (_breathingRate < 6)
    {
        _breathingRate = 6;
    }

    if (_breathingRate > 40)
    {
        _breathingRate = 40;
    }
}

float BreathingEngine::currentFrequency() const
{
    return _frequency;
}

int BreathingEngine::currentBreathingRate() const
{
    return _breathingRate;
}