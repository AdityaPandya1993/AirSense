//
//  DeviceController.cpp
//  AirSense Firmware
//

#include "DeviceController.h"

DeviceController&
DeviceController::shared()
{
    static DeviceController controller;

    return controller;
}

DeviceController::DeviceController()
{
    _status = "READY";

    _uptime = 0;

    _heap = 0;

    _human.detected = false;
    _human.personCount = 0;
    _human.motion = "Idle";
    _human.heartRate = 0;
    _human.breathing = 0;
    _human.x = 0.0f;
    _human.y = 0.0f;
}

void DeviceController::update()
{
    _uptime = millis() / 1000;

    _heap = ESP.getFreeHeap();
}


void DeviceController::updateHuman(
    const HumanEntity& human
)
{
    _human = human;
}

//--------------------------------------------------
// Device
//--------------------------------------------------

const String&
DeviceController::status() const
{
    return _status;
}

uint32_t
DeviceController::uptime() const
{
    return _uptime;
}

uint32_t
DeviceController::heap() const
{
    return _heap;
}

//--------------------------------------------------
// Human
//--------------------------------------------------

int
DeviceController::personCount() const
{
    return _human.personCount;
}

const String&
DeviceController::motion() const
{
    return _human.motion;
}

int
DeviceController::heartRate() const
{
    return _human.heartRate;
}

int
DeviceController::breathing() const
{
    return _human.breathing;
}

bool
DeviceController::detected() const
{
    return _human.detected;
}

float
DeviceController::positionX() const
{
    return _human.x;
}

float
DeviceController::positionY() const
{
    return _human.y;
}

//--------------------------------------------------
// Manual Override
//--------------------------------------------------

void DeviceController::setStatus(
    const String& value
)
{
    _status = value;
}

void DeviceController::setPersonCount(
    int value
)
{
    _human.personCount = value;
}

void DeviceController::setMotion(
    const String& value
)
{
    _human.motion = value;
}

void DeviceController::setHeartRate(
    int value
)
{
    _human.heartRate = value;
}

void DeviceController::setBreathing(
    int value
)
{
    _human.breathing = value;
}