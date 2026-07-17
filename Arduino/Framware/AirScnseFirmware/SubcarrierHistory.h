//
//  SubcarrierHistory.h
//  AirSense Firmware
//

#ifndef SUBCARRIER_HISTORY_H
#define SUBCARRIER_HISTORY_H

#include "DSPConstants.h"
#include "CSIFrame.h"

class SubcarrierHistory
{
public:

    static SubcarrierHistory& shared();

    void update(
        const CSIFrame& frame
    );

    float sample(
        int subcarrier,
        int index
    ) const;

    int sampleCount() const;

private:

    SubcarrierHistory();

private:

    float _history
        [DSP::SubcarrierCount]
        [DSP::FFTSize];

    int _head;

    int _count;
};

#endif