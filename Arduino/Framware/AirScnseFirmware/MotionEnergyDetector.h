//
//  MotionEnergyDetector.h
//  AirSense Firmware
//

#ifndef MOTION_ENERGY_DETECTOR_H
#define MOTION_ENERGY_DETECTOR_H

class MotionEnergyDetector
{
public:

    static MotionEnergyDetector& shared();

    void update(float energy);

    float motionEnergy() const;

    bool isMoving() const;

private:

    MotionEnergyDetector();

private:

    float _motionEnergy;
};

#endif