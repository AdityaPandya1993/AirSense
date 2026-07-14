//
//  HumanStateMachine.cpp
//  AirSense Firmware
//

#include "HumanStateMachine.h"

HumanStateMachine&
HumanStateMachine::shared()
{
    static HumanStateMachine machine;

    return machine;
}

HumanStateMachine::HumanStateMachine()
{
    _state = HumanState::Booting;
}

HumanState
HumanStateMachine::currentState() const
{
    return _state;
}

void HumanStateMachine::nextState()
{
    switch (_state)
    {
        case HumanState::Booting:

            _state = HumanState::Idle;
            break;

        case HumanState::Idle:

            _state = HumanState::PersonDetected;
            break;

        case HumanState::PersonDetected:

            _state = HumanState::Monitoring;
            break;

        case HumanState::Monitoring:

            _state = HumanState::GestureDetected;
            break;

        case HumanState::GestureDetected:

            _state = HumanState::Alert;
            break;

        case HumanState::Alert:

            _state = HumanState::Idle;
            break;
    }
}