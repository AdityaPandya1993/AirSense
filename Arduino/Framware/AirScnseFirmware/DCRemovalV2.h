//
//  DCRemovalV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//

#ifndef DC_REMOVAL_V2_H
#define DC_REMOVAL_V2_H

#include <Arduino.h>

class DCRemovalV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static DCRemovalV2& shared();

    //--------------------------------------------------
    // Remove DC Component
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Information
    //--------------------------------------------------

    float mean() const;

private:

    DCRemovalV2();

    float _mean;
};

#endif