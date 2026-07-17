//
//  VarianceAnalyzer.cpp
//  AirSense Firmware
//
//  Version : 2.0
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
    _currentVariance = 0.0f;
}

void VarianceAnalyzer::update(
    const float* samples,
    int count
)
{
    if (count <= 1)
    {
        _currentVariance = 0.0f;
        return;
    }

    //--------------------------------------------------
    // Mean
    //--------------------------------------------------

    float mean = 0.0f;

    for (int i = 0; i < count; i++)
    {
        mean += samples[i];
    }

    mean /= count;

    //--------------------------------------------------
    // Variance
    //--------------------------------------------------

    float variance = 0.0f;

    for (int i = 0; i < count; i++)
    {
        float diff = samples[i] - mean;
        variance += diff * diff;
    }

    variance /= (count - 1);

    _currentVariance = variance;
}

float VarianceAnalyzer::currentVariance() const
{
    return _currentVariance;
}