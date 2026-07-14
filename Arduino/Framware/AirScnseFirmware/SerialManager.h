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

    private:

    static void handlePing();

    static void handleHello();

    static void handleStatus();

    

    public:

    static void begin();

    static void processIncomingCommand();

    static void sendStatus();

    static void sendHeartbeat();
};

#endif