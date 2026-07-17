//
//  EnergyAnalyzer.cpp
//  AirSense Firmware
//
//  Version : 2.0
//

#include "EnergyAnalyzer.h"
#include <math.h>

EnergyAnalyzer&
EnergyAnalyzer::shared()
{
    static EnergyAnalyzer analyzer;
    return analyzer;
}

EnergyAnalyzer::EnergyAnalyzer()
{
    _currentEnergy = 0.0f;
}

void EnergyAnalyzer::update(
    const float* samples,
    int count
)
{
    if (count <= 0)
    {
        _currentEnergy = 0.0f;
        return;
    }

    //--------------------------------------------------
    // RMS Energy
    //--------------------------------------------------

    float energy = 0.0f;

    for (int i = 0; i < count; i++)
    {
        energy += samples[i] * samples[i];
    }

    energy /= count;

    _currentEnergy = sqrtf(energy);
}

float EnergyAnalyzer::currentEnergy() const
{
    return _currentEnergy;
}