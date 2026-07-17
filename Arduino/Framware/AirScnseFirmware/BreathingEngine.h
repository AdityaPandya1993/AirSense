//
//  BreathingEngine.h
//  AirSense Firmware
//
//  Version : 2.0
//  Phase   : Professional Firmware
//

#ifndef BREATHING_ENGINE_H
#define BREATHING_ENGINE_H

class BreathingEngine
{
public:

    static BreathingEngine& shared();

    void update(
        float frequency
    );

    float currentFrequency() const;

    int currentBreathingRate() const;

private:

    BreathingEngine();

private:

    float _frequency;

    int _breathingRate;
};

#endif