//
//  SubcarrierSelector.cpp
//  AirSense Firmware
//
//  Version : 3.0
//

#include "SubcarrierSelector.h"

#include "DSPConstants.h"
#include "SubcarrierHistory.h"
#include <math.h>

SubcarrierSelector&
SubcarrierSelector::shared()
{
    static SubcarrierSelector selector;
    return selector;
}

SubcarrierSelector::SubcarrierSelector()
{
    _bestSubcarrier = 0;
    _quality = -1.0f;
}

void SubcarrierSelector::analyze()
{
    _bestSubcarrier = 0;
    _quality = -999999.0f;

    float samples[DSP::FFTSize];

    for (int subcarrier = 0;
         subcarrier < DSP::SubcarrierCount;
         subcarrier++)
    {
        int count =
            SubcarrierHistory::shared()
                .sampleCount();

        if (count < 2)
        {
            continue;
        }

        //--------------------------------------------------
        // Copy History
        //--------------------------------------------------

        for (int i = 0; i < count; i++)
        {
            samples[i] =
                SubcarrierHistory::shared()
                    .sample(subcarrier, i);
        }

        //--------------------------------------------------
        // Simple Stability Score
        //
        // NOTE:
        // This class ONLY selects the best carrier.
        // No analyzers are updated here.
        //--------------------------------------------------

        float score = 0.0f;

        for (int i = 1; i < count; i++)
        {
            score -= fabsf(
                samples[i] -
                samples[i - 1]
            );
        }

        //--------------------------------------------------
        // Keep Best
        //--------------------------------------------------

        if (score > _quality)
        {
            _quality = score;
            _bestSubcarrier = subcarrier;
        }
    }
}

int SubcarrierSelector::bestSubcarrier() const
{
    return _bestSubcarrier;
}

float SubcarrierSelector::quality() const
{
    return _quality;
}