//
//  HeartEngine.cpp
//  AirSense Firmware
//

#include "HeartEngine.h"
#include "FrequencyAnalyzer.h"

HeartEngine&
HeartEngine::shared()
{
    static HeartEngine engine;
    return engine;
}

HeartEngine::HeartEngine()
{
    _heartRate = 0;
    _valid = false;
}

void HeartEngine::update(
    float frequency
)
{
    float bpm =
        FrequencyAnalyzer::shared()
            .frequencyToBPM(frequency);

    if (bpm >= 48.0f &&
        bpm <= 150.0f)
    {
        _heartRate =
            (int)(bpm + 0.5f);

        _valid = true;
    }
    else
    {
        _heartRate = 0;
        _valid = false;
    }
}

int HeartEngine::heartRate() const
{
    return _heartRate;
}

bool HeartEngine::validSignal() const
{
    return _valid;
}