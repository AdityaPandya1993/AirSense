//
//  HeartEngine.cpp
//  AirSense Firmware
//
//  Version : 2.0
//  Phase   : Professional Firmware
//

#include "HeartEngine.h"

HeartEngine&
HeartEngine::shared()
{
    static HeartEngine engine;

    return engine;
}

HeartEngine::HeartEngine()
{
    _frequency = 0.0f;
    _heartRate = 0;
}

void HeartEngine::update(
    float frequency
)
{
    _frequency = frequency;

    _heartRate =
        (int)(frequency * 60.0f);

    //--------------------------------------------------
    // Clamp
    //--------------------------------------------------

    if (_heartRate < 40)
    {
        _heartRate = 40;
    }

    if (_heartRate > 180)
    {
        _heartRate = 180;
    }
}

float HeartEngine::currentFrequency() const
{
    return _frequency;
}

int HeartEngine::currentHeartRate() const
{
    return _heartRate;
}