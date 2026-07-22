//
//  BandPassFilter.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2
//

#include "BandPassFilter.h"
#include "SignalBuffer.h"

BandPassFilter&
BandPassFilter::shared()
{
    static BandPassFilter filter;

    return filter;
}

BandPassFilter::BandPassFilter()
{
    _hpPreviousInput = 0.0f;
    _hpPreviousOutput = 0.0f;

    _lpPreviousOutput = 0.0f;

    for (uint16_t i = 0; i < MAX_SAMPLES; i++)
    {
        _filtered[i] = 0.0f;
    }
}

void BandPassFilter::process()
{
    const float* input =
        SignalBuffer::shared().samples();

    uint16_t count =
        SignalBuffer::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Band Pass Filtering
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        //----------------------------------------------
        // High Pass
        //----------------------------------------------

        float hp =
            HP_ALPHA *
            (
                _hpPreviousOutput +
                input[i] -
                _hpPreviousInput
            );

        _hpPreviousInput = input[i];
        _hpPreviousOutput = hp;

        //----------------------------------------------
        // Low Pass
        //----------------------------------------------

        float lp =
            _lpPreviousOutput +
            LP_ALPHA *
            (
                hp -
                _lpPreviousOutput
            );

        _lpPreviousOutput = lp;

        _filtered[i] = lp;
    }

    //--------------------------------------------------
    // Update Shared Signal Buffer
    //--------------------------------------------------

    SignalBuffer::shared().update(
        _filtered,
        count
    );
}