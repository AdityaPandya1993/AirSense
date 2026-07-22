//
//  HumanStateEngineV2.cpp
//  AirSense Firmware
//

#include "HumanStateEngineV2.h"

HumanStateEngineV2&
HumanStateEngineV2::shared()
{
    static HumanStateEngineV2 instance;
    return instance;
}

////////////////////////////////////////////////////////

HumanStateEngineV2::HumanStateEngineV2()
{
    reset();
}

////////////////////////////////////////////////////////

void HumanStateEngineV2::reset()
{
    _state = HumanStateV2::NoHuman;
    _humanPresent = false;
}

////////////////////////////////////////////////////////

void HumanStateEngineV2::update(
    bool motionDetected,
    float heartBPM,
    float breathingRPM,
    float confidence,
    float signalQuality
)
{
    //--------------------------------------------------
    // Human Detection
    //--------------------------------------------------

    if(confidence < 0.30f ||
       signalQuality < 0.30f)
    {
        _state = HumanStateV2::NoHuman;
        _humanPresent = false;
        return;
    }

    _humanPresent = true;

    //--------------------------------------------------
    // Emergency
    //--------------------------------------------------

    if(heartBPM > 170.0f ||
       breathingRPM > 35.0f)
    {
        _state = HumanStateV2::Emergency;
        return;
    }

    //--------------------------------------------------
    // Fall
    //--------------------------------------------------

    if(motionDetected &&
       heartBPM < 45.0f)
    {
        _state = HumanStateV2::FallSuspected;
        return;
    }

    //--------------------------------------------------
    // Sleeping
    //--------------------------------------------------

    if(!motionDetected &&
       heartBPM < 65.0f &&
       breathingRPM < 15.0f)
    {
        _state = HumanStateV2::Sleeping;
        return;
    }

    //--------------------------------------------------
    // Walking
    //--------------------------------------------------

    if(motionDetected &&
       heartBPM < 110.0f)
    {
        _state = HumanStateV2::Walking;
        return;
    }

    //--------------------------------------------------
    // Running
    //--------------------------------------------------

    if(motionDetected &&
       heartBPM >= 110.0f)
    {
        _state = HumanStateV2::Running;
        return;
    }

    //--------------------------------------------------
    // Monitoring
    //--------------------------------------------------

    _state = HumanStateV2::Monitoring;
}

////////////////////////////////////////////////////////

HumanStateV2
HumanStateEngineV2::currentState() const
{
    return _state;
}

////////////////////////////////////////////////////////

bool
HumanStateEngineV2::humanPresent() const
{
    return _humanPresent;
}

////////////////////////////////////////////////////////

const char*
HumanStateEngineV2::stateString() const
{
    switch(_state)
    {
        case HumanStateV2::NoHuman:
            return "No Human";

        case HumanStateV2::HumanDetected:
            return "Human Detected";

        case HumanStateV2::Monitoring:
            return "Monitoring";

        case HumanStateV2::Sleeping:
            return "Sleeping";

        case HumanStateV2::Walking:
            return "Walking";

        case HumanStateV2::Running:
            return "Running";

        case HumanStateV2::FallSuspected:
            return "Fall Suspected";

        case HumanStateV2::Emergency:
            return "Emergency";

        default:
            return "Unknown";
    }
}