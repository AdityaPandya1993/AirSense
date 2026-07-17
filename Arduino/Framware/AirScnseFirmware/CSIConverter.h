//
//  CSIConverter.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef CSI_CONVERTER_H
#define CSI_CONVERTER_H

#include <Arduino.h>

#include "IQSample.h"
#include "CSISample.h"

#define MAX_CSI_SAMPLES 192

class CSIConverter
{
public:

    static CSIConverter& shared();

    //--------------------------------------------------
    // Convert IQ -> CSI
    //--------------------------------------------------

    void convert(
        const IQSample* iqSamples,
        uint16_t count
    );

    //--------------------------------------------------
    // Access Converted Samples
    //--------------------------------------------------

    const CSISample* samples() const;

    //--------------------------------------------------
    // Sample Count
    //--------------------------------------------------

    uint16_t sampleCount() const;

private:

    CSIConverter();

private:

    CSISample _samples[MAX_CSI_SAMPLES];

    uint16_t _sampleCount;
};

#endif