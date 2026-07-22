//
//  WindowFunction.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2
//

#include "WindowFunction.h"
#include "SignalBuffer.h"

WindowFunction&
WindowFunction::shared()
{
    static WindowFunction window;

    return window;
}

WindowFunction::WindowFunction()
{
    for (uint16_t i = 0; i < MAX_SAMPLES; i++)
    {
        _window[i] = 0.0f;
    }
}

void WindowFunction::process()
{
    float temp[MAX_SAMPLES];

    const float* input =
        SignalBuffer::shared().samples();

    uint16_t count =
        SignalBuffer::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Build Hamming Window
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        _window[i] =
            0.54f -
            0.46f *
            cosf(
                2.0f *
                PI *
                i /
                (count - 1)
            );
    }

    //--------------------------------------------------
    // Apply Window
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        temp[i] =
            input[i] *
            _window[i];
    }

    //--------------------------------------------------
    // Update Shared Buffer
    //--------------------------------------------------

    SignalBuffer::shared().update(
        temp,
        count
    );
}