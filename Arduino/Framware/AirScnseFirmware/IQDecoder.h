//
//  IQDecoder.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef IQ_DECODER_H
#define IQ_DECODER_H

#include <Arduino.h>

#include "RawCSIFrame.h"
#include "IQSample.h"

#define MAX_IQ_SAMPLES 192

class IQDecoder
{
public:

    static IQDecoder& shared();

    //--------------------------------------------------
    // Decode Raw CSI Packet
    //--------------------------------------------------

    void decode(
        const RawCSIFrame& frame
    );

    //--------------------------------------------------
    // Access Decoded Samples
    //--------------------------------------------------

    const IQSample* samples() const;

    //--------------------------------------------------
    // Total IQ Samples
    //--------------------------------------------------

    uint16_t sampleCount() const;

private:

    IQDecoder();

private:

    IQSample _samples[MAX_IQ_SAMPLES];

    uint16_t _sampleCount;
};

#endif