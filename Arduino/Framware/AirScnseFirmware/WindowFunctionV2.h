//
//  WindowFunctionV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//

#ifndef WINDOW_FUNCTION_V2_H
#define WINDOW_FUNCTION_V2_H

#include <Arduino.h>

class WindowFunctionV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static WindowFunctionV2& shared();

    //--------------------------------------------------
    // Apply Window
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    void printDebug() const;

private:

    WindowFunctionV2();

    //--------------------------------------------------
    // Window Functions
    //--------------------------------------------------

    float rectangular(
        uint16_t index,
        uint16_t count
    ) const;

    float hamming(
        uint16_t index,
        uint16_t count
    ) const;

    float hann(
        uint16_t index,
        uint16_t count
    ) const;

    float blackman(
        uint16_t index,
        uint16_t count
    ) const;
};

#endif