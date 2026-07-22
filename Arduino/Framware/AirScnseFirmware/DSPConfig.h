//
//  DSPConfig.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//
//  Created by Aditya Pandya
//

#ifndef DSP_CONFIG_H
#define DSP_CONFIG_H

#include <Arduino.h>

namespace DSPConfig
{
    //--------------------------------------------------
    // General
    //--------------------------------------------------

    static constexpr uint16_t MAX_SAMPLES = 256;

    static constexpr uint16_t FFT_SIZE = 256;

    static constexpr uint16_t SUBCARRIER_COUNT = 128;

    static constexpr float SAMPLE_RATE = 10.0f;

    //--------------------------------------------------
    // DC Removal
    //--------------------------------------------------

    static constexpr bool ENABLE_DC_REMOVAL = true;

    //--------------------------------------------------
    // Low Pass Filter
    //--------------------------------------------------

    static constexpr bool ENABLE_LOW_PASS = true;

    static constexpr float LOW_PASS_ALPHA = 0.25f;

    //--------------------------------------------------
    // High Pass Filter
    //--------------------------------------------------

    static constexpr bool ENABLE_HIGH_PASS = true;

    static constexpr float HIGH_PASS_ALPHA = 0.95f;

    //--------------------------------------------------
    // Window Function
    //--------------------------------------------------

    enum class WindowType
    {
        Rectangular,
        Hamming,
        Hann,
        Blackman
    };

    static constexpr WindowType WINDOW =
        WindowType::Hamming;

    //--------------------------------------------------
    // Heart Detection
    //--------------------------------------------------

    static constexpr float HEART_MIN_HZ = 0.80f;

    static constexpr float HEART_MAX_HZ = 3.00f;

    //--------------------------------------------------
    // Breathing Detection
    //--------------------------------------------------

    static constexpr float BREATH_MIN_HZ = 0.10f;

    static constexpr float BREATH_MAX_HZ = 0.60f;

    //--------------------------------------------------
    // Motion Energy
    //--------------------------------------------------

    static constexpr float STILL_THRESHOLD = 0.20f;

    static constexpr float SMALL_MOTION_THRESHOLD = 1.00f;

    static constexpr float LARGE_MOTION_THRESHOLD = 3.00f;

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    static constexpr bool PRINT_DSP = true;

    static constexpr bool PRINT_FILTERS = true;

    static constexpr bool PRINT_FFT = true;

    static constexpr bool PRINT_PEAK = true;

    static constexpr bool PRINT_HEART = true;

    static constexpr bool PRINT_BREATHING = true;

    static constexpr bool PRINT_CONFIDENCE = true;
}

#endif