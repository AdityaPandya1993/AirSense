//
//  EnergyAnalyzer.h
//  AirSense Firmware
//
//  Version : 2.0
//

#ifndef ENERGY_ANALYZER_H
#define ENERGY_ANALYZER_H

class EnergyAnalyzer
{
public:

    static EnergyAnalyzer& shared();

    void update(
        const float* samples,
        int count
    );

    float currentEnergy() const;

private:

    EnergyAnalyzer();

private:

    float _currentEnergy;
};

#endif