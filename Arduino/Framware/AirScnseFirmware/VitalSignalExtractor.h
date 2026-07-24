//
// VitalSignalExtractor.h
// AirSense Firmware
//

#ifndef VITAL_SIGNAL_EXTRACTOR_H
#define VITAL_SIGNAL_EXTRACTOR_H

#include <Arduino.h>

class VitalSignalExtractor
{
public:

    static VitalSignalExtractor& shared();

    void begin();

    float process(
        const float* amplitude,
        uint16_t count
    );

private:

    VitalSignalExtractor();

    float movingAverage(
        const float* signal,
        uint16_t count
    );

    float variance(
        const float* signal,
        uint16_t count
    );

};

#endif