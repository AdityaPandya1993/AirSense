//
//  HumanStateMachine.h
//  AirSense Firmware
//

#ifndef HUMAN_STATE_MACHINE_H
#define HUMAN_STATE_MACHINE_H

#include "HumanState.h"

class HumanStateMachine
{
public:

    static HumanStateMachine& shared();

    HumanState currentState() const;

    void nextState();

private:

    HumanStateMachine();

    HumanState _state;
};

#endif