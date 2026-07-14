//
//  Protocol.h
//  AirSense Firmware
//
//  AirSense Communication Protocol v1.0
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <Arduino.h>

enum class MessageType
{
    Heartbeat,
    DeviceInfo,
    Person,
    Pet,
    CSI,
    Alert
};

struct HeartbeatPacket
{
    String deviceName;

    String firmwareVersion;

    String status;

    uint32_t uptime;

    uint32_t freeHeap;
};


#endif