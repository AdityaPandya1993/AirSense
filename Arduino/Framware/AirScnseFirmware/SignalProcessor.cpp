//
//  SignalProcessor.cpp
//  AirSense Firmware
//

#include "SignalProcessor.h"
#include "DSPConstants.h"

SignalProcessor&
SignalProcessor::shared()
{
    static SignalProcessor processor;
    return processor;
}

SignalProcessor::SignalProcessor()
{
    for (int i = 0; i < DSP::SubcarrierCount; i++)
    {
        _filtered[i] = 0.0f;
        _mean[i] = 0.0f;
        _normalized[i] = 0.0f;
        _lowPass[i] = 0.0f;
        _breathing[i] = 0.0f;
        _heart[i] = 0.0f;
    }
}

void SignalProcessor::process(
    const CSIFrame& frame
)
{
    for (int i = 0; i < DSP::SubcarrierCount; i++)
    {
        //--------------------------------------------------
        // Moving Average
        //--------------------------------------------------

        _filtered[i] =
            (_filtered[i] *
             (1.0f - DSP::MovingAverageAlpha))
            +
            (frame.subcarriers[i] *
             DSP::MovingAverageAlpha);

        //--------------------------------------------------
        // DC Removal
        //--------------------------------------------------

        _mean[i] =
            (_mean[i] *
             (1.0f - DSP::DCRemovalAlpha))
            +
            (_filtered[i] *
             DSP::DCRemovalAlpha);

        _filtered[i] =
            _filtered[i] - _mean[i];

        //--------------------------------------------------
        // Normalization
        //--------------------------------------------------

        _normalized[i] =
            _filtered[i] /
            DSP::MaxAmplitude;

        if (_normalized[i] > 1.0f)
        {
            _normalized[i] = 1.0f;
        }

        if (_normalized[i] < -1.0f)
        {
            _normalized[i] = -1.0f;
        }

        //--------------------------------------------------
        // Low Pass
        //--------------------------------------------------

        _lowPass[i] =
            (_lowPass[i] *
             (1.0f - DSP::LowPassAlpha))
            +
            (_normalized[i] *
             DSP::LowPassAlpha);

        //--------------------------------------------------
        // Breathing Filter
        //--------------------------------------------------

        _breathing[i] =
            (_breathing[i] *
             (1.0f - DSP::BreathingAlpha))
            +
            (_lowPass[i] *
             DSP::BreathingAlpha);

        //--------------------------------------------------
        // Heart Filter
        //--------------------------------------------------

        _heart[i] =
            (_heart[i] *
             (1.0f - DSP::HeartAlpha))
            +
            (_lowPass[i] *
             DSP::HeartAlpha);
    }
}

float SignalProcessor::filteredSubcarrier(
    int index
) const
{
    if (index < 0 || index >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    return _filtered[index];
}

float SignalProcessor::normalizedSubcarrier(
    int index
) const
{
    if (index < 0 || index >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    return _normalized[index];
}

float SignalProcessor::lowPassSubcarrier(
    int index
) const
{
    if (index < 0 || index >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    return _lowPass[index];
}

float SignalProcessor::breathingSubcarrier(
    int index
) const
{
    if (index < 0 || index >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    return _breathing[index];
}

float SignalProcessor::heartSubcarrier(
    int index
) const
{
    if (index < 0 || index >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    return _heart[index];
}