//
//  PeakDetectorV3.cpp
//  AirSense Firmware
//

#include "PeakDetectorV3.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

PeakDetectorV3&
PeakDetectorV3::shared()
{
    static PeakDetectorV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

PeakDetectorV3::PeakDetectorV3()
{
    reset();
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool PeakDetectorV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void PeakDetectorV3::reset()
{
    _ready = false;

    _peakIndex = 0;

    _peakMagnitude = 0.0f;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void PeakDetectorV3::process(
    const float* magnitude,
    uint16_t count
)
{
    if (!_ready)
    {
        return;
    }

    if (magnitude == nullptr)
    {
        return;
    }

    _peakIndex = 0;

    _peakMagnitude = 0.0f;

    //--------------------------------------------------
    // Ignore DC Component
    //--------------------------------------------------

    for(uint16_t i = 1;
        i < count / 2;
        i++)
    {
        if(magnitude[i] > _peakMagnitude)
        {
            _peakMagnitude = magnitude[i];

            _peakIndex = i;
        }
    }
}

////////////////////////////////////////////////////////
// Peak Index
////////////////////////////////////////////////////////

uint16_t
PeakDetectorV3::peakIndex() const
{
    return _peakIndex;
}

////////////////////////////////////////////////////////
// Peak Magnitude
////////////////////////////////////////////////////////

float
PeakDetectorV3::peakMagnitude() const
{
    return _peakMagnitude;
}