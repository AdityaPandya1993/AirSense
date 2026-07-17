//
//  SubcarrierHistory.cpp
//  AirSense Firmware
//

#include "SubcarrierHistory.h"

SubcarrierHistory&
SubcarrierHistory::shared()
{
    static SubcarrierHistory history;

    return history;
}

SubcarrierHistory::SubcarrierHistory()
{
    _head = 0;
    _count = 0;

    for (int i = 0; i < DSP::SubcarrierCount; i++)
    {
        for (int j = 0; j < DSP::FFTSize; j++)
        {
            _history[i][j] = 0.0f;
        }
    }
}

void SubcarrierHistory::update(
    const CSIFrame& frame
)
{
    for (int i = 0; i < DSP::SubcarrierCount; i++)
    {
        _history[i][_head] =
            frame.subcarriers[i];
    }

    _head++;

    if (_head >= DSP::FFTSize)
    {
        _head = 0;
    }

    if (_count < DSP::FFTSize)
    {
        _count++;
    }
}

float SubcarrierHistory::sample(
    int subcarrier,
    int index
) const
{
    if (subcarrier < 0 ||
        subcarrier >= DSP::SubcarrierCount)
    {
        return 0.0f;
    }

    if (index < 0 ||
        index >= _count)
    {
        return 0.0f;
    }

    int start = _head - _count;

    if (start < 0)
    {
        start += DSP::FFTSize;
    }

    int realIndex =
        (start + index) %
        DSP::FFTSize;

    return _history[subcarrier][realIndex];
}

int SubcarrierHistory::sampleCount() const
{
    return _count;
}