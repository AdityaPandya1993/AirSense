//
//  FFTPeakDetector.cpp
//  AirSense Firmware
//

#include "FFTPeakDetector.h"

FFTPeakDetector&
FFTPeakDetector::shared()
{
    static FFTPeakDetector instance;

    return instance;
}

FFTPeakDetector::FFTPeakDetector()
{
    reset();
}

void FFTPeakDetector::reset()
{
    _peakIndex = 0;
    _peakMagnitude = 0.0f;

    _secondPeakIndex = 0;
    _secondPeakMagnitude = 0.0f;

    _noiseFloor = 0.0f;
}

void FFTPeakDetector::detect(
    const float* spectrum,
    uint16_t fftSize
)
{
    if (spectrum == nullptr || fftSize == 0)
    {
        return;
    }

    reset();

    float sum = 0.0f;

    //--------------------------------------------------
    // Skip DC Component (index 0)
    //--------------------------------------------------

    for (uint16_t i = 1; i < fftSize / 2; i++)
    {
        float value = spectrum[i];

        sum += value;

        if (value > _peakMagnitude)
        {
            _secondPeakMagnitude = _peakMagnitude;
            _secondPeakIndex = _peakIndex;

            _peakMagnitude = value;
            _peakIndex = i;
        }
        else if (value > _secondPeakMagnitude)
        {
            _secondPeakMagnitude = value;
            _secondPeakIndex = i;
        }
    }

    _noiseFloor =
        sum / float((fftSize / 2) - 1);
}

////////////////////////////////////////////////////////

uint16_t FFTPeakDetector::peakIndex() const
{
    return _peakIndex;
}

float FFTPeakDetector::peakMagnitude() const
{
    return _peakMagnitude;
}

////////////////////////////////////////////////////////

uint16_t FFTPeakDetector::secondPeakIndex() const
{
    return _secondPeakIndex;
}

float FFTPeakDetector::secondPeakMagnitude() const
{
    return _secondPeakMagnitude;
}

////////////////////////////////////////////////////////

float FFTPeakDetector::noiseFloor() const
{
    return _noiseFloor;
}