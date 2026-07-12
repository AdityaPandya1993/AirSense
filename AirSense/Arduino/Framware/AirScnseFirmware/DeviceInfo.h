//
//  DeviceInfo.h
//  AirSense Firmware
//
//  Version : 0.3.0
//

#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <Arduino.h>

struct DeviceInfo
{
    //==================================================
    // Device
    //==================================================

    String deviceName;

    String firmwareVersion;

    String chipModel;

    //==================================================
    // Status
    //==================================================

    String status;

    //==================================================
    // System
    //==================================================

    uint32_t uptime;

    uint32_t freeHeap;

    //==================================================
    // Room
    //==================================================

    uint8_t personCount;

    uint8_t petCount;

};

#endif