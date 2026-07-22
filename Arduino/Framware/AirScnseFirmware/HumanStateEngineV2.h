//
//  HumanStateEngineV2.h
//  AirSense Firmware
//

#ifndef HUMAN_STATE_ENGINE_V2_H
#define HUMAN_STATE_ENGINE_V2_H

#include <Arduino.h>

enum class HumanStateV2
{
    NoHuman,
    HumanDetected,
    Monitoring,
    Sleeping,
    Walking,
    Running,
    FallSuspected,
    Emergency
};

class HumanStateEngineV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static HumanStateEngineV2& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update(
        bool motionDetected,
        float heartBPM,
        float breathingRPM,
        float confidence,
        float signalQuality
    );

    //--------------------------------------------------
    // State
    //--------------------------------------------------

    HumanStateV2 currentState() const;

    const char* stateString() const;

    bool humanPresent() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    HumanStateEngineV2();

private:

    HumanStateV2 _state;

    bool _humanPresent;
};

#endif