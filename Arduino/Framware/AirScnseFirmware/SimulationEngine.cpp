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
#include "SignalWindow.h"

#include "DSPPipeline.h"

void SimulationEngine::update()
{
    static unsigned long lastUpdate = 0;

    Serial.println("SimulationEngine Enter");

    // if (millis() - lastUpdate < 5000)
    // {
    //     return;
    // }

    lastUpdate = millis();
    Serial.println("5 Seconds Completed");

    //--------------------------------------------------
    // Generate Simulated CSI Frame
    //--------------------------------------------------

    CSIManager::shared().update();

    CSIBuffer::shared().addFrame(
        CSIManager::shared().currentFrame()
    );

    //--------------------------------------------------
    // Run Complete DSP Pipeline
    //--------------------------------------------------
    Serial.println("Before DSP");
    DSPPipeline::shared().process(
        CSIManager::shared().currentFrame()
    );
    Serial.println("After DSP");

    //--------------------------------------------------
    // Signal Window
    //--------------------------------------------------

    SignalWindow::shared().addFrame(
        CSIManager::shared().currentFrame()
    );

    //--------------------------------------------------
    // Generate Simulated Human
    //--------------------------------------------------

    HumanEntity human;
    Serial.println("Calling updateHuman()");
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


Serial.println();
Serial.println("===== HUMAN BEFORE UPDATE =====");

Serial.print("Detected : ");
Serial.println(human.detected);

Serial.print("Persons  : ");
Serial.println(human.personCount);

Serial.print("Motion   : ");
Serial.println(human.motion);

Serial.print("Heart    : ");
Serial.println(human.heartRate);

Serial.print("Breath   : ");
Serial.println(human.breathing);

Serial.print("X        : ");
Serial.println(human.x);

Serial.print("Y        : ");
Serial.println(human.y);

Serial.println("===============================");
Serial.println();
    //--------------------------------------------------
    // Update Device
    //--------------------------------------------------
    Serial.println("Calling updateHuman()");
    DeviceController::shared().updateHuman(
        human
    );

    Serial.println(">>> updateHuman() called");

Serial.print("Persons = ");
Serial.println(human.personCount);

Serial.print("Motion = ");
Serial.println(human.motion);

Serial.print("Heart = ");
Serial.println(human.heartRate);

Serial.print("Breath = ");
Serial.println(human.breathing);

    //--------------------------------------------------
    // Move To Next Simulation State
    //--------------------------------------------------

    HumanStateMachine::shared().nextState();
}