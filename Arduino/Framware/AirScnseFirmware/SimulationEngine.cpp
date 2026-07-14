//
//  SimulationEngine.cpp
//  AirSense Firmware
//

#include "SimulationEngine.h"
#include "DeviceController.h"
#include "HumanEntity.h"
#include "HumanState.h"
#include "HumanStateMachine.h"

#include "CSIManager.h"
#include "CSIBuffer.h"
#include "SignalProcessor.h" //Very Impoernt 
#include "SignalWindow.h"

void SimulationEngine::update()
{
    static unsigned long lastUpdate = 0;

    if (millis() - lastUpdate < 5000)
    {
        return;
    }

    lastUpdate = millis();

    // -------------------------------------------------
    // Generate Simulated CSI Frame
    // -------------------------------------------------

    CSIManager::shared().update();

    CSIBuffer::shared().addFrame(
        CSIManager::shared().currentFrame()
    );

    //This is a Main File..
    SignalProcessor::shared().process(
    CSIManager::shared().currentFrame()
    );

    //Single Window wait for 128 Frame Then Ready = true then new frame slide old frame out
    SignalWindow::shared().addFrame(
    CSIManager::shared().currentFrame()
);

    // -------------------------------------------------
    // Generate Simulated Human
    // -------------------------------------------------

    HumanEntity human;

    HumanState state =
        HumanStateMachine::shared().currentState();

    switch (state)
    {
        case HumanState::Idle:

            human.state = HumanState::Idle;
            human.detected = false;
            human.personCount = 0;
            human.motion = "Idle";
            human.heartRate = 0;
            human.breathing = 0;
            human.x = 0.0f;
            human.y = 0.0f;

            break;

        case HumanState::PersonDetected:

            human.state = HumanState::PersonDetected;
            human.detected = true;
            human.personCount = 1;
            human.motion = "Standing";
            human.heartRate = 72;
            human.breathing = 15;
            human.x = 2.0f;
            human.y = 1.5f;

            break;

        case HumanState::Monitoring:

            human.state = HumanState::Monitoring;
            human.detected = true;
            human.personCount = 1;
            human.motion = "Walking";
            human.heartRate = 81;
            human.breathing = 18;
            human.x = 2.3f;
            human.y = 1.8f;

            break;

        case HumanState::GestureDetected:

            human.state = HumanState::GestureDetected;
            human.detected = true;
            human.personCount = 1;
            human.motion = "Running";
            human.heartRate = 110;
            human.breathing = 24;
            human.x = 2.8f;
            human.y = 2.2f;

            break;

        case HumanState::Alert:

            human.state = HumanState::Alert;
            human.detected = true;
            human.personCount = 1;
            human.motion = "Falling";
            human.heartRate = 135;
            human.breathing = 30;
            human.x = 3.0f;
            human.y = 2.5f;

            break;
    }

    DeviceController::shared().updateHuman(human);

    HumanStateMachine::shared().nextState();
}