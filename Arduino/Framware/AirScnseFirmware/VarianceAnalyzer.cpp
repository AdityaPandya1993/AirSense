//
//  VarianceAnalyzer.cpp
//  AirSense Firmware
//

#include "VarianceAnalyzer.h"

VarianceAnalyzer&
VarianceAnalyzer::shared()
{
    static VarianceAnalyzer analyzer;

    return analyzer;
}

VarianceAnalyzer::VarianceAnalyzer()
{
    _variance = 0.0f;
    _mean = 0.0f;
}

void VarianceAnalyzer::update(
    const float* samples,
    uint16_t count
)
{
    if (count == 0)
    {
        _mean = 0.0f;
        _variance = 0.0f;
        return;
    }

    //--------------------------------------------------
    // Mean
    //--------------------------------------------------

    float sum = 0.0f;

    for (uint16_t i = 0; i < count; i++)
    {
        sum += samples[i];
    }

    _mean = sum / count;

    //--------------------------------------------------
    // Variance
    //--------------------------------------------------

    float varianceSum = 0.0f;

    for (uint16_t i = 0; i < count; i++)
    {
        float diff = samples[i] - _mean;

        varianceSum += diff * diff;
    }

    _variance = varianceSum / count;
}

float
VarianceAnalyzer::currentVariance() const
{
    return _variance;
}

float
VarianceAnalyzer::currentMean() const
{
    return _mean;
}