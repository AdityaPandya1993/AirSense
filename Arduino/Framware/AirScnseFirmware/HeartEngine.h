//
//  HeartEngine.h
//  AirSense Firmware
//

#ifndef HEART_ENGINE_H
#define HEART_ENGINE_H

class HeartEngine
{
public:

    static HeartEngine& shared();

    void update(float frequency);

    int heartRate() const;

    bool validSignal() const;

private:

    HeartEngine();

    int _heartRate;

    bool _valid;
};

#endif