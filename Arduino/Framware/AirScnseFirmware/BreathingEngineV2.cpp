//
//  BreathingEngineV2.cpp
//  AirSense Firmware
//

#include "BreathingEngineV2.h"

BreathingEngineV2&
BreathingEngineV2::shared()
{
    static BreathingEngineV2 instance;

    return instance;
}

////////////////////////////////////////////////////////

BreathingEngineV2::BreathingEngineV2()
{
    reset();
}

////////////////////////////////////////////////////////

void BreathingEngineV2::reset()
{
    _index = 0;

    _currentRPM = 0.0f;

    _filteredRPM = 0.0f;

    _confidence = 0.0f;

    _valid = false;

    for(uint8_t i=0;i<FILTER_SIZE;i++)
    {
        _history[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////

void BreathingEngineV2::update(
    float respirationRPM,
    float confidence
)
{
    _currentRPM = respirationRPM;

    _confidence = confidence;

    //--------------------------------------------------
    // Human Respiration Range
    //--------------------------------------------------

    if(respirationRPM < 4.0f)
    {
        _valid = false;
        return;
    }

    if(respirationRPM > 45.0f)
    {
        _valid = false;
        return;
    }

    //--------------------------------------------------
    // Confidence
    //--------------------------------------------------

    if(confidence < 0.30f)
    {
        _valid = false;
        return;
    }

    movingAverage(
        respirationRPM
    );

    _valid = true;
}

////////////////////////////////////////////////////////

void BreathingEngineV2::movingAverage(
    float rpm
)
{
    _history[_index] = rpm;

    _index++;

    if(_index >= FILTER_SIZE)
    {
        _index = 0;
    }

    float sum = 0.0f;

    for(uint8_t i=0;i<FILTER_SIZE;i++)
    {
        sum += _history[i];
    }

    _filteredRPM =
        sum /
        FILTER_SIZE;
}

////////////////////////////////////////////////////////

float BreathingEngineV2::currentRPM() const
{
    return _currentRPM;
}

////////////////////////////////////////////////////////

float BreathingEngineV2::filteredRPM() const
{
    return _filteredRPM;
}

////////////////////////////////////////////////////////

float BreathingEngineV2::confidence() const
{
    return _confidence;
}

////////////////////////////////////////////////////////

bool BreathingEngineV2::isValid() const
{
    return _valid;
}