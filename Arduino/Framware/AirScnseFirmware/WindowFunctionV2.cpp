//
//  WindowFunctionV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//

#include "WindowFunctionV2.h"

#include <math.h>

#include "SignalBufferV2.h"
#include "DSPConfig.h"

WindowFunctionV2&
WindowFunctionV2::shared()
{
    static WindowFunctionV2 instance;

    return instance;
}

WindowFunctionV2::WindowFunctionV2()
{

}

void WindowFunctionV2::reset()
{

}

void WindowFunctionV2::process()
{
    float* samples =
        SignalBufferV2::shared().workingSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        float coefficient = 1.0f;

        switch (DSPConfig::WINDOW)
        {
            case DSPConfig::WindowType::Rectangular:

                coefficient =
                    rectangular(i, count);

                break;

            case DSPConfig::WindowType::Hamming:

                coefficient =
                    hamming(i, count);

                break;

            case DSPConfig::WindowType::Hann:

                coefficient =
                    hann(i, count);

                break;

            case DSPConfig::WindowType::Blackman:

                coefficient =
                    blackman(i, count);

                break;
        }

        samples[i] *= coefficient;
    }
}

float
WindowFunctionV2::rectangular(
    uint16_t,
    uint16_t
) const
{
    return 1.0f;
}

float
WindowFunctionV2::hamming(
    uint16_t index,
    uint16_t count
) const
{
    return
        0.54f -
        0.46f *
        cosf(
            2.0f *
            PI *
            index /
            (count - 1)
        );
}

float
WindowFunctionV2::hann(
    uint16_t index,
    uint16_t count
) const
{
    return
        0.5f *
        (
            1.0f -
            cosf(
                2.0f *
                PI *
                index /
                (count - 1)
            )
        );
}

float
WindowFunctionV2::blackman(
    uint16_t index,
    uint16_t count
) const
{
    return
        0.42f
        -
        0.50f *
        cosf(
            2.0f *
            PI *
            index /
            (count - 1)
        )
        +
        0.08f *
        cosf(
            4.0f *
            PI *
            index /
            (count - 1)
        );
}

void
WindowFunctionV2::printDebug() const
{
    Serial.println();
    Serial.println(F("----------------------------------------"));
    Serial.println(F("WINDOW FUNCTION V2"));
    Serial.println();

    Serial.print(F("Samples : "));
    Serial.println(
        SignalBufferV2::shared().sampleCount()
    );

    Serial.print(F("Window  : "));

    switch (DSPConfig::WINDOW)
    {
        case DSPConfig::WindowType::Rectangular:

            Serial.println(F("Rectangular"));
            break;

        case DSPConfig::WindowType::Hamming:

            Serial.println(F("Hamming"));
            break;

        case DSPConfig::WindowType::Hann:

            Serial.println(F("Hann"));
            break;

        case DSPConfig::WindowType::Blackman:

            Serial.println(F("Blackman"));
            break;
    }
}