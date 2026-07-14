//
//  BreathingEngine.h
//  AirSense Firmware
//

#ifndef BREATHING_ENGINE_H
#define BREATHING_ENGINE_H

class BreathingEngine
{
public:

    static BreathingEngine& shared();

    void update(float frequency);

    int breathingRate() const;

    bool validSignal() const;

private:

    BreathingEngine();

    int _breathingRate;

    bool _valid;
};

#endif