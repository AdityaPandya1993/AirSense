//
//  RawCSIFrame.h
//  AirSense Firmware
//

#ifndef RAW_CSI_FRAME_H
#define RAW_CSI_FRAME_H

#include <Arduino.h>

#define RAW_CSI_MAX_LENGTH 512

struct RawCSIFrame
{
    //--------------------------------------------------
    // Metadata
    //--------------------------------------------------

    uint64_t timestamp;

    int8_t rssi;

    uint8_t channel;

    uint16_t length;

    bool firstWordInvalid;

    //--------------------------------------------------
    // Raw CSI Bytes
    //--------------------------------------------------

    int8_t data[RAW_CSI_MAX_LENGTH];
};

#endif