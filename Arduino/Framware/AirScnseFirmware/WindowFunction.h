//
//  WindowFunction.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2
//

#ifndef WINDOW_FUNCTION_H
#define WINDOW_FUNCTION_H

#include <Arduino.h>

class WindowFunction
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static WindowFunction& shared();

    //--------------------------------------------------
    // Apply Hamming Window
    //--------------------------------------------------

    void process();

private:

    WindowFunction();

    static constexpr uint16_t MAX_SAMPLES = 256;

    float _window[MAX_SAMPLES];
};

#endif