//
//  SerialManager.h
//  AirSense Firmware
//

#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include <Arduino.h>
#include "Protocol.h"

class SerialManager
{
public:

    static void begin();

    static void sendHeartbeat(
        const HeartbeatPacket& packet
    );
};

#endif