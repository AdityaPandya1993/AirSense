//
//  SignalBufferV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.1
//
//  Created by Aditya Pandya
//

#include "SignalBufferV2.h"

SignalBufferV2&
SignalBufferV2::shared()
{
    static SignalBufferV2 buffer;

    return buffer;
}

SignalBufferV2::SignalBufferV2()
{
    reset();
}

//--------------------------------------------------
// Update Raw Buffer
//--------------------------------------------------

void SignalBufferV2::updateRaw(
    const float* samples,
    uint16_t count
)
{
    if (count > MAX_SAMPLES)
    {
        count = MAX_SAMPLES;
    }

    _count = count;

    for (uint16_t i = 0; i < count; i++)
    {
        _raw[i] = samples[i];
    }
}

//--------------------------------------------------
// Raw Buffer
//--------------------------------------------------

const float*
SignalBufferV2::rawSamples() const
{
    return _raw;
}

//--------------------------------------------------
// Working Buffer
//--------------------------------------------------

float*
SignalBufferV2::workingSamples()
{
    return _working;
}

const float*
SignalBufferV2::workingSamples() const
{
    return _working;
}

//--------------------------------------------------
// FFT Buffer
//--------------------------------------------------

float*
SignalBufferV2::fftSamples()
{
    return _fft;
}

const float*
SignalBufferV2::fftSamples() const
{
    return _fft;
}

//--------------------------------------------------
// Spectrum Buffer
//--------------------------------------------------

float*
SignalBufferV2::spectrum()
{
    return _spectrum;
}

const float*
SignalBufferV2::spectrum() const
{
    return _spectrum;
}

//--------------------------------------------------
// Copy Raw -> Working
//--------------------------------------------------

void SignalBufferV2::copyRawToWorking()
{
    for (uint16_t i = 0; i < _count; i++)
    {
        _working[i] = _raw[i];
    }
}

//--------------------------------------------------
// Copy Working -> FFT
//--------------------------------------------------

void SignalBufferV2::copyWorkingToFFT()
{
    for (uint16_t i = 0; i < _count; i++)
    {
        _fft[i] = _working[i];
    }
}

//--------------------------------------------------
// Clear Buffers
//--------------------------------------------------

void SignalBufferV2::clear()
{
    for (uint16_t i = 0; i < MAX_SAMPLES; i++)
    {
        _raw[i] = 0.0f;
        _working[i] = 0.0f;
        _fft[i] = 0.0f;
        _spectrum[i] = 0.0f;
    }

    _count = 0;
}

//--------------------------------------------------
// Reset
//--------------------------------------------------

void SignalBufferV2::reset()
{
    clear();
}

//--------------------------------------------------
// Sample Count
//--------------------------------------------------

uint16_t
SignalBufferV2::sampleCount() const
{
    return _count;
}

//--------------------------------------------------
// Capacity
//--------------------------------------------------

uint16_t
SignalBufferV2::capacity() const
{
    return MAX_SAMPLES;
}