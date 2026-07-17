//
//  DSPConstants.h
//

#ifndef DSP_CONSTANTS_H
#define DSP_CONSTANTS_H

#include <Arduino.h>

namespace DSP
{
    //--------------------------------------------------
    // Mathematical Constants
    //--------------------------------------------------

    constexpr float kPi =
        3.14159265358979323846f;

    constexpr float kTwoPi =
        6.28318530717958647692f;

    //--------------------------------------------------
    // CSI
    //--------------------------------------------------

    constexpr int SubcarrierCount = 64;

    constexpr int FFTSize = 128;

    //--------------------------------------------------
    // Filters
    //--------------------------------------------------

    constexpr float MovingAverageAlpha = 0.20f;

    constexpr float DCRemovalAlpha = 0.005f;

    constexpr float LowPassAlpha = 0.15f;

    constexpr float BreathingAlpha = 0.05f;

    constexpr float HeartAlpha = 0.30f;

    constexpr float MaxAmplitude = 3.0f;

    constexpr float SampleRate = 20.0f;
}

#endif