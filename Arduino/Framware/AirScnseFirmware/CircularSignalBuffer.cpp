//
//  CircularSignalBuffer.cpp
//  AirSense Firmware
//
//  DSP V4
//

#include "CircularSignalBuffer.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

CircularSignalBuffer&
CircularSignalBuffer::shared()
{
    static CircularSignalBuffer instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

CircularSignalBuffer::CircularSignalBuffer()
{
    _writeIndex = 0;

    _filled = false;

    _totalSamples = 0;

    for (uint16_t i = 0; i < DSPConfig::FFT_SIZE; i++)
    {
        _buffer[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

void CircularSignalBuffer::begin()
{
    reset();

    Serial.println("[DSP] Circular Signal Buffer Ready");
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void CircularSignalBuffer::reset()
{
    _writeIndex = 0;

    _filled = false;

    _totalSamples = 0;

    for (uint16_t i = 0; i < DSPConfig::FFT_SIZE; i++)
{
    _buffer[i] = 0.0f;
    _linearBuffer[i] = 0.0f;
}
}
////////////////////////////////////////////////////////
// Push Samples
////////////////////////////////////////////////////////

void CircularSignalBuffer::push(
    const float* samples,
    uint16_t count
)
{
    if (samples == nullptr)
    {
        return;
    }

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Copy Incoming Samples
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        _buffer[_writeIndex] = samples[i];

        _writeIndex++;

        if (_writeIndex >= DSPConfig::FFT_SIZE)
        {
            _writeIndex = 0;

            _filled = true;
        }

        _totalSamples++;
    }
}
////////////////////////////////////////////////////////
// Ready
////////////////////////////////////////////////////////

bool CircularSignalBuffer::ready() const
{
    return _filled;
}

////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////

const float*
CircularSignalBuffer::data()
{
    if (!_filled)
    {
        return _buffer;
    }

    uint16_t index = _writeIndex;

    for (uint16_t i = 0; i < DSPConfig::FFT_SIZE; i++)
    {
        _linearBuffer[i] = _buffer[index];

        index++;

        if (index >= DSPConfig::FFT_SIZE)
        {
            index = 0;
        }
    }

    return _linearBuffer;
}

////////////////////////////////////////////////////////
// Size
////////////////////////////////////////////////////////

uint16_t
CircularSignalBuffer::size() const
{
    return DSPConfig::FFT_SIZE;
}

////////////////////////////////////////////////////////
// Total Samples
////////////////////////////////////////////////////////

uint32_t
CircularSignalBuffer::totalSamples() const
{
    return _totalSamples;
}