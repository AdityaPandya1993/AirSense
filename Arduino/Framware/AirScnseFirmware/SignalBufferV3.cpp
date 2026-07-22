//
//  SignalBufferV3.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "SignalBufferV3.h"
#include "SharedDSPWorkspace.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

SignalBufferV3&
SignalBufferV3::shared()
{
    static SignalBufferV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

SignalBufferV3::SignalBufferV3()
{
    _sampleCount = 0;
    _ready = false;
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool SignalBufferV3::begin()
{
    if (_ready)
    {
        return true;
    }

    _ready =
        SharedDSPWorkspace
            ::shared()
            .begin();

    return _ready;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void SignalBufferV3::reset()
{
    _sampleCount = 0;

    if (!_ready)
    {
        return;
    }

    float* buffer = samples();

    if (buffer == nullptr)
    {
        return;
    }

    for (uint16_t i = 0;
         i < MAX_SAMPLES;
         i++)
    {
        buffer[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////

void SignalBufferV3::update(
    const float* input,
    uint16_t count
)
{
    if (!_ready)
    {
        return;
    }

    if (count > MAX_SAMPLES)
    {
        count = MAX_SAMPLES;
    }

    float* buffer = samples();

    if (buffer == nullptr)
    {
        return;
    }

    _sampleCount = count;

    for (uint16_t i = 0;
         i < count;
         i++)
    {
        buffer[i] = input[i];
    }
}

////////////////////////////////////////////////////////
// Samples
////////////////////////////////////////////////////////

float*
SignalBufferV3::samples()
{
    return
        SharedDSPWorkspace
            ::shared()
            .signal();
}

const float*
SignalBufferV3::samples() const
{
    return
        SharedDSPWorkspace
            ::shared()
            .signal();
}

////////////////////////////////////////////////////////
// Sample
////////////////////////////////////////////////////////

float
SignalBufferV3::sample(
    uint16_t index
) const
{
    if (index >= _sampleCount)
    {
        return 0.0f;
    }

    return samples()[index];
}

////////////////////////////////////////////////////////
// Sample Count
////////////////////////////////////////////////////////

uint16_t
SignalBufferV3::sampleCount() const
{
    return _sampleCount;
}

////////////////////////////////////////////////////////
// Capacity
////////////////////////////////////////////////////////

uint16_t
SignalBufferV3::capacity() const
{
    return MAX_SAMPLES;
}

////////////////////////////////////////////////////////
// Ready
////////////////////////////////////////////////////////

bool
SignalBufferV3::isReady() const
{
    return _ready;
}