//
//  BreathingEngine.cpp
//  AirSense Firmware
//

#include "BreathingEngine.h"
#include "FrequencyAnalyzer.h"

BreathingEngine&
BreathingEngine::shared()
{
    static BreathingEngine engine;

    return engine;
}

BreathingEngine::BreathingEngine()
{
    _breathingRate = 0;
    _valid = false;
}

void BreathingEngine::update(
    float frequency
)
{
    float bpm =
        FrequencyAnalyzer::shared()
            .frequencyToBPM(frequency);

    if (bpm >= 6.0f &&
        bpm <= 30.0f)
    {
        _breathingRate =
            (int)(bpm + 0.5f);

        _valid = true;
    }
    else
    {
        _breathingRate = 0;
        _valid = false;
    }
}

int BreathingEngine::breathingRate() const
{
    return _breathingRate;
}

bool BreathingEngine::validSignal() const
{
    return _valid;
}