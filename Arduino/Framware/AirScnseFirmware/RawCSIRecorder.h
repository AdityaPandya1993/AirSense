//
//  RawCSIRecorder.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef RAW_CSI_RECORDER_H
#define RAW_CSI_RECORDER_H

#include "RawCSIFrame.h"

class RawCSIRecorder
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static RawCSIRecorder& shared();

    //--------------------------------------------------
    // Lifecycle
    //--------------------------------------------------

    void begin();

    //--------------------------------------------------
    // Recording
    //--------------------------------------------------

    void record(
        const RawCSIFrame& frame
    );

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    RawCSIFrame latestFrame() const;

    uint64_t packetCount() const;

    bool hasFrame() const;

private:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    RawCSIRecorder();

private:

    //--------------------------------------------------
    // Storage
    //--------------------------------------------------

    RawCSIFrame _latestFrame;

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    uint64_t _packetCount;

    bool _frameAvailable;
};

#endif