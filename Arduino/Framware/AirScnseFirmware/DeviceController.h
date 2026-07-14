//
//  DeviceController.h
//  AirSense Firmware
//

#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <Arduino.h>
#include "HumanEntity.h"

class DeviceController
{
public:

    static DeviceController& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update();

    void updateHuman(
        const HumanEntity& human
    );

    //--------------------------------------------------
    // Device Information
    //--------------------------------------------------

    const String& status() const;

    uint32_t uptime() const;

    uint32_t heap() const;

    //--------------------------------------------------
    // Human Information
    //--------------------------------------------------

    int personCount() const;

    const String& motion() const;

    int heartRate() const;

    int breathing() const;

    bool detected() const;

    float positionX() const;

    float positionY() const;

    //--------------------------------------------------
    // Manual Override
    //--------------------------------------------------

    void setStatus(
        const String& value
    );

    void setPersonCount(
        int value
    );

    void setMotion(
        const String& value
    );

    void setHeartRate(
        int value
    );

    void setBreathing(
        int value
    );

private:

    DeviceController();

private:

    String _status;

    uint32_t _uptime;

    uint32_t _heap;

    HumanEntity _human;
};

#endif