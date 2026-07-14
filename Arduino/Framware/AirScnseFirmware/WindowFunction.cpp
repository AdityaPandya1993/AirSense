//
//  WindowFunction.cpp
//  AirSense Firmware
//

#include "WindowFunction.h"
#include "DSPConstants.h"

#include <math.h>

WindowFunction&
WindowFunction::shared()
{
    static WindowFunction window;

    return window;
}

WindowFunction::WindowFunction()
{

}

void WindowFunction::apply(
    float* samples,
    int count
)
{
    if (samples == nullptr || count <= 1)
    {
        return;
    }

    //--------------------------------------------------
    // Hann Window
    //--------------------------------------------------

    for (int i = 0; i < count; i++)
    {
        float multiplier =
            0.5f -
            0.5f *
            cosf(
                (DSP::kTwoPi * float(i))
                /
                float(count - 1)
            );

        samples[i] *= multiplier;
    }
}