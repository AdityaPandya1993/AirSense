//
//  HumanEntity.h
//  AirSense Firmware
//

#ifndef HUMAN_ENTITY_H
#define HUMAN_ENTITY_H

#include <Arduino.h>
#include "HumanState.h"

struct HumanEntity
{
    HumanState state;

    bool detected;

    int personCount;

    String motion;

    int heartRate;

    int breathing;

    float x;

    float y;
};

#endif