//
//  PeakDetector.h
//  AirSense Firmware
//

#ifndef PEAK_DETECTOR_H
#define PEAK_DETECTOR_H

class PeakDetector
{
public:

    static PeakDetector& shared();

    int findPeak(
        const float* spectrum,
        int count
    );

    float peakValue() const;

private:

    PeakDetector();

    int _peakIndex;

    float _peakValue;
};

#endif