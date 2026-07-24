//
// VitalSignalExtractor.cpp
//

#include "VitalSignalExtractor.h"

VitalSignalExtractor&
VitalSignalExtractor::shared()
{
    static VitalSignalExtractor instance;
    return instance;
}

VitalSignalExtractor::VitalSignalExtractor()
{
}

void VitalSignalExtractor::begin()
{
}

float VitalSignalExtractor::movingAverage(
    const float* signal,
    uint16_t count
)
{
    float sum = 0;

    for(uint16_t i=0;i<count;i++)
    {
        sum += signal[i];
    }

    return sum / count;
}

float VitalSignalExtractor::variance(
    const float* signal,
    uint16_t count
)
{
    float mean =
        movingAverage(signal,count);

    float total = 0;

    for(uint16_t i=0;i<count;i++)
    {
        float d =
            signal[i]-mean;

        total += d*d;
    }

    return total / count;
}

float VitalSignalExtractor::process(
    const float* amplitude,
    uint16_t count
)
{
    return variance(
        amplitude,
        count
    );
}