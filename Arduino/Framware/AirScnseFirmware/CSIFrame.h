//
//  CSIFrame.h
//  AirSense Firmware
//

#ifndef CSI_FRAME_H
#define CSI_FRAME_H

#include <Arduino.h>

struct CSIFrame
{
    uint32_t timestamp;

    int rssi;

    int noise;

    uint16_t sequence;

    uint8_t channel;

    uint8_t bandwidth;

    float subcarriers[64];
};

#endif