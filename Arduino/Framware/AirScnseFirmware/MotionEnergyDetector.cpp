//
//  MotionEnergyDetector.cpp
//  AirSense Firmware
//

#include "MotionEnergyDetector.h"

MotionEnergyDetector&
MotionEnergyDetector::shared()
{
    static MotionEnergyDetector detector;

    return detector;
}

MotionEnergyDetector::MotionEnergyDetector()
{
    _motionEnergy = 0.0f;
}

void MotionEnergyDetector::update(
    float energy
)
{
    //--------------------------------------------------
    // Simple Low Pass
    //--------------------------------------------------

    _motionEnergy =
        (_motionEnergy * 0.8f) +
        (energy * 0.2f);
}

float MotionEnergyDetector::motionEnergy() const
{
    return _motionEnergy;
}

bool MotionEnergyDetector::isMoving() const
{
    return _motionEnergy > 0.35f;
}