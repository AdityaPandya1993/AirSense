//
//  HeartEngine.h
//  AirSense Firmware
//
//  Version : 2.0
//  Phase   : Professional Firmware
//

#ifndef HEART_ENGINE_H
#define HEART_ENGINE_H

class HeartEngine
{
public:

    static HeartEngine& shared();

    void update(
        float frequency
    );

    float currentFrequency() const;

    int currentHeartRate() const;

private:

    HeartEngine();

private:

    float _frequency;

    int _heartRate;
};

#endif