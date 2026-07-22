//
//  HeartEngineV2.cpp
//  AirSense Firmware
//

#include "HeartEngineV2.h"

HeartEngineV2&
HeartEngineV2::shared()
{
    static HeartEngineV2 instance;

    return instance;
}

HeartEngineV2::HeartEngineV2()
{
    reset();
}

////////////////////////////////////////////////////////

void HeartEngineV2::reset()
{
    _index = 0;

    _currentBPM = 0.0f;

    _filteredBPM = 0.0f;

    _confidence = 0.0f;

    _valid = false;

    for (uint8_t i = 0;
         i < FILTER_SIZE;
         i++)
    {
        _history[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////

void HeartEngineV2::update(
    float heartBPM,
    float confidence
)
{
    //--------------------------------------------------
    // Store
    //--------------------------------------------------

    _currentBPM = heartBPM;

    _confidence = confidence;

    //--------------------------------------------------
    // Human Heart Range
    //--------------------------------------------------

    if (heartBPM < 35.0f ||
        heartBPM > 220.0f)
    {
        _valid = false;

        return;
    }

    //--------------------------------------------------
    // Confidence
    //--------------------------------------------------

    if (confidence < 0.30f)
    {
        _valid = false;

        return;
    }

    //--------------------------------------------------
    // Moving Average
    //--------------------------------------------------

    movingAverage(
        heartBPM
    );

    _valid = true;
}

////////////////////////////////////////////////////////

void HeartEngineV2::movingAverage(
    float bpm
)
{
    _history[_index] = bpm;

    _index++;

    if (_index >= FILTER_SIZE)
    {
        _index = 0;
    }

    float sum = 0.0f;

    for (uint8_t i = 0;
         i < FILTER_SIZE;
         i++)
    {
        sum += _history[i];
    }

    _filteredBPM =
        sum /
        FILTER_SIZE;
}

////////////////////////////////////////////////////////

float HeartEngineV2::currentBPM() const
{
    return _currentBPM;
}

float HeartEngineV2::filteredBPM() const
{
    return _filteredBPM;
}

float HeartEngineV2::confidence() const
{
    return _confidence;
}

bool HeartEngineV2::isValid() const
{
    return _valid;
}