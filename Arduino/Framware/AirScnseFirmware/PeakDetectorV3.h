//
//  PeakDetectorV3.h
//  AirSense Firmware
//

#ifndef PEAK_DETECTOR_V3_H
#define PEAK_DETECTOR_V3_H

#include <Arduino.h>

class PeakDetectorV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static PeakDetectorV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Process
    //--------------------------------------------------

    void process(
        const float* magnitude,
        uint16_t count
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    uint16_t peakIndex() const;

    float peakMagnitude() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    PeakDetectorV3();

private:

    bool _ready;

    uint16_t _peakIndex;

    float _peakMagnitude;
};

#endif