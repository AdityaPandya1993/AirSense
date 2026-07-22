//
//  HumanStateMachine.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
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

void HumanStateMachine::reset()
{
    _state = HumanState::Booting;
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

            _state = HumanState::Still;
            break;

        case HumanState::Still:

            _state = HumanState::Monitoring;
            break;

        case HumanState::Monitoring:

            _state = HumanState::Walking;
            break;

        case HumanState::Walking:

            _state = HumanState::Running;
            break;

        case HumanState::Running:

            _state = HumanState::GestureDetected;
            break;

        case HumanState::GestureDetected:

            _state = HumanState::FallDetected;
            break;

        case HumanState::FallDetected:

            _state = HumanState::Alert;
            break;

        case HumanState::Alert:

            _state = HumanState::Idle;
            break;
    }
}

void HumanStateMachine::update(
    bool personDetected,
    float filteredMotionEnergy
)
{
    //--------------------------------------------------
    // No Person
    //--------------------------------------------------

    if (!personDetected)
    {
        _state = HumanState::Idle;
        return;
    }

    //--------------------------------------------------
    // Person Found
    //--------------------------------------------------

    if (_state == HumanState::Booting)
    {
        _state = HumanState::PersonDetected;
    }

    //--------------------------------------------------
    // Motion Decision
    //--------------------------------------------------

    if (filteredMotionEnergy < 0.02f)
    {
        _state = HumanState::Still;
    }
    else if (filteredMotionEnergy < 0.20f)
    {
        _state = HumanState::Monitoring;
    }
    else if (filteredMotionEnergy < 1.00f)
    {
        _state = HumanState::Walking;
    }
    else if (filteredMotionEnergy < 3.00f)
    {
        _state = HumanState::Running;
    }
    else
    {
        _state = HumanState::Alert;
    }
}