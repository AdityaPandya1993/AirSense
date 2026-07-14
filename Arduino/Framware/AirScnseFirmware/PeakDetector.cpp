//
//  PeakDetector.cpp
//  AirSense Firmware
//

#include "PeakDetector.h"

PeakDetector&
PeakDetector::shared()
{
    static PeakDetector detector;

    return detector;
}

PeakDetector::PeakDetector()
{
    _peakIndex = 0;
    _peakValue = 0.0f;
}

int PeakDetector::findPeak(
    const float* spectrum,
    int count
)
{
    _peakIndex = 0;
    _peakValue = 0.0f;

    if (spectrum == nullptr || count <= 0)
    {
        return 0;
    }

    for (int i = 1; i < count; i++)
    {
        if (spectrum[i] > _peakValue)
        {
            _peakValue = spectrum[i];
            _peakIndex = i;
        }
    }

    return _peakIndex;
}

float PeakDetector::peakValue() const
{
    return _peakValue;
}