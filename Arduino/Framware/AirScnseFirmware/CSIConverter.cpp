//
//  CSIConverter.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "CSIConverter.h"

#include <math.h>

CSIConverter&
CSIConverter::shared()
{
    static CSIConverter converter;
    return converter;
}

CSIConverter::CSIConverter()
{
    _sampleCount = 0;
}

void CSIConverter::convert(
    const IQSample* iqSamples,
    uint16_t count
)
{
    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    _sampleCount = count;

    if (_sampleCount > MAX_CSI_SAMPLES)
    {
        _sampleCount = MAX_CSI_SAMPLES;
    }

    //--------------------------------------------------
    // Convert IQ → CSI
    //--------------------------------------------------

    for (uint16_t i = 0; i < _sampleCount; i++)
    {
        float iValue =
            (float)iqSamples[i].i;

        float qValue =
            (float)iqSamples[i].q;

        //--------------------------------------------------
        // Sample Index
        //--------------------------------------------------

        _samples[i].index = i;

        //--------------------------------------------------
        // Amplitude
        //--------------------------------------------------

        _samples[i].amplitude =
            sqrt(
                (iValue * iValue) +
                (qValue * qValue)
            );

        //--------------------------------------------------
        // Phase
        //--------------------------------------------------

        _samples[i].phase =
            atan2(
                qValue,
                iValue
            );
    }
}

const CSISample*
CSIConverter::samples() const
{
    return _samples;
}

uint16_t
CSIConverter::sampleCount() const
{
    return _sampleCount;
}