//
//  HumanState.h
//  AirSense Firmware
//

#ifndef HUMAN_STATE_H
#define HUMAN_STATE_H

enum class HumanState
{
    Booting,

    Idle,

    PersonDetected,

    Monitoring,

    GestureDetected,

    Alert
};

#endif