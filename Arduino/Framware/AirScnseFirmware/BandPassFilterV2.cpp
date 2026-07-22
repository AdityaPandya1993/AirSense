//
//  BandPassFilterV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//
//  Created by Aditya Pandya
//

#include "BandPassFilterV2.h"

#include "SignalBufferV2.h"
#include "DSPConfig.h"

BandPassFilterV2&
BandPassFilterV2::shared()
{
    static BandPassFilterV2 instance;

    return instance;
}

BandPassFilterV2::BandPassFilterV2()
{
    reset();
}

void BandPassFilterV2::reset()
{
    _previousInput = 0.0f;
    _previousHighPass = 0.0f;
    _previousLowPass = 0.0f;
}

void BandPassFilterV2::process()
{
    float* samples =
        SignalBufferV2::shared().workingSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // High Pass + Low Pass
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        //----------------------------------------------
        // High Pass
        //----------------------------------------------

        float highPass =
            DSPConfig::HIGH_PASS_ALPHA *
            (
                _previousHighPass +
                samples[i] -
                _previousInput
            );

        _previousInput = samples[i];
        _previousHighPass = highPass;

        //----------------------------------------------
        // Low Pass
        //----------------------------------------------

        float lowPass =
            _previousLowPass +
            DSPConfig::LOW_PASS_ALPHA *
            (
                highPass -
                _previousLowPass
            );

        _previousLowPass = lowPass;

        //----------------------------------------------
        // Store Back
        //----------------------------------------------

        samples[i] = lowPass;
    }
}

void BandPassFilterV2::printDebug() const
{
    Serial.println();

    Serial.println(F("----------------------------------------"));
    Serial.println(F("BAND PASS FILTER V2"));
    Serial.println();

    Serial.print(F("High Pass Alpha : "));
    Serial.println(
        DSPConfig::HIGH_PASS_ALPHA,
        3
    );

    Serial.print(F("Low Pass Alpha  : "));
    Serial.println(
        DSPConfig::LOW_PASS_ALPHA,
        3
    );

    Serial.print(F("Sample Count    : "));
    Serial.println(
        SignalBufferV2::shared().sampleCount()
    );
}

float
BandPassFilterV2::highPassAlpha() const
{
    return DSPConfig::HIGH_PASS_ALPHA;
}

float
BandPassFilterV2::lowPassAlpha() const
{
    return DSPConfig::LOW_PASS_ALPHA;
}