//
//  SharedDSPWorkspace.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "SharedDSPWorkspace.h"

#include <esp_heap_caps.h>

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

SharedDSPWorkspace&
SharedDSPWorkspace::shared()
{
    static SharedDSPWorkspace instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

SharedDSPWorkspace::SharedDSPWorkspace()
{
    _ready = false;

    _signal = nullptr;
    _fftReal = nullptr;
    _fftImag = nullptr;
    _magnitude = nullptr;
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool SharedDSPWorkspace::begin()
{
    if (_ready)
    {
        return true;
    }

    const size_t bytes =
        BUFFER_SIZE * sizeof(float);

    //--------------------------------------------------
    // Allocate PSRAM
    //--------------------------------------------------

    _signal =
        (float*)ps_malloc(bytes);

    _fftReal =
        (float*)ps_malloc(bytes);

    _fftImag =
        (float*)ps_malloc(bytes);

    _magnitude =
        (float*)ps_malloc(bytes);

    //--------------------------------------------------
    // Allocation Check
    //--------------------------------------------------

    if (_signal == nullptr ||
        _fftReal == nullptr ||
        _fftImag == nullptr ||
        _magnitude == nullptr)
    {
        Serial.println(
            "[DSP] PSRAM Allocation Failed"
        );

        release();

        return false;
    }

    //--------------------------------------------------
    // Clear Memory
    //--------------------------------------------------

    reset();

    _ready = true;

    Serial.println(
        "[DSP] Shared Workspace Ready"
    );

    return true;
}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void SharedDSPWorkspace::reset()
{
    if (!_signal)
    {
        return;
    }

    for(uint16_t i = 0;
        i < BUFFER_SIZE;
        i++)
    {
        _signal[i] = 0.0f;
        _fftReal[i] = 0.0f;
        _fftImag[i] = 0.0f;
        _magnitude[i] = 0.0f;
    }
}

////////////////////////////////////////////////////////
// Release
////////////////////////////////////////////////////////

void SharedDSPWorkspace::release()
{
    if (_signal)
    {
        free(_signal);
        _signal = nullptr;
    }

    if (_fftReal)
    {
        free(_fftReal);
        _fftReal = nullptr;
    }

    if (_fftImag)
    {
        free(_fftImag);
        _fftImag = nullptr;
    }

    if (_magnitude)
    {
        free(_magnitude);
        _magnitude = nullptr;
    }

    _ready = false;
}

////////////////////////////////////////////////////////
// Signal
////////////////////////////////////////////////////////

float*
SharedDSPWorkspace::signal()
{
    return _signal;
}

////////////////////////////////////////////////////////
// FFT Real
////////////////////////////////////////////////////////

float*
SharedDSPWorkspace::fftReal()
{
    return _fftReal;
}

////////////////////////////////////////////////////////
// FFT Imaginary
////////////////////////////////////////////////////////

float*
SharedDSPWorkspace::fftImag()
{
    return _fftImag;
}

////////////////////////////////////////////////////////
// Magnitude
////////////////////////////////////////////////////////

float*
SharedDSPWorkspace::magnitude()
{
    return _magnitude;
}

////////////////////////////////////////////////////////
// Capacity
////////////////////////////////////////////////////////

uint16_t
SharedDSPWorkspace::capacity() const
{
    return BUFFER_SIZE;
}

////////////////////////////////////////////////////////
// Ready
////////////////////////////////////////////////////////

bool
SharedDSPWorkspace::ready() const
{
    return _ready;
}