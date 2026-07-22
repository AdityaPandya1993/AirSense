//
//  FFTProcessorV2.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//

#include "FFTProcessorV2.h"

#include "SignalBufferV2.h"
#include "DSPConfig.h"

FFTProcessorV2&
FFTProcessorV2::shared()
{
    static FFTProcessorV2 instance;

    return instance;
}

FFTProcessorV2::FFTProcessorV2()
{
    reset();
}

void FFTProcessorV2::reset()
{
    _peakIndex = 0;
    _peakMagnitude = 0.0f;

    for (uint16_t i = 0; i < MAX_SAMPLES; i++)
    {
        _real[i] = 0.0f;
        _imag[i] = 0.0f;
    }
}

void FFTProcessorV2::process()
{
    //--------------------------------------------------
    // FFT Input
    //--------------------------------------------------

    const float* samples =
        SignalBufferV2::shared().fftSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Copy To Internal Buffer
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        _real[i] = samples[i];
        _imag[i] = 0.0f;
    }

    //--------------------------------------------------
    // Clear Remaining
    //--------------------------------------------------

    for (uint16_t i = count; i < MAX_SAMPLES; i++)
    {
        _real[i] = 0.0f;
        _imag[i] = 0.0f;
    }

    //--------------------------------------------------
    // Stage 1
    //--------------------------------------------------

    bitReverse();

    //--------------------------------------------------
    // Stage 2
    //--------------------------------------------------

    computeFFT();

    //--------------------------------------------------
    // Stage 3
    //--------------------------------------------------

    computeMagnitude();

    //--------------------------------------------------
    // Stage 4
    //--------------------------------------------------

    findPeak();
}

//////////////////////////////////////////////////////
// Bit Reversal
//////////////////////////////////////////////////////

void FFTProcessorV2::bitReverse()
{
    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Calculate Bit Count
    //--------------------------------------------------

    uint8_t bits = 0;

    uint16_t value = count;

    while (value > 1)
    {
        bits++;
        value >>= 1;
    }

    //--------------------------------------------------
    // Reorder Samples
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        uint16_t j =
            reverseBits(i, bits);

        if (j > i)
        {
            float temp;

            temp = _real[i];
            _real[i] = _real[j];
            _real[j] = temp;

            temp = _imag[i];
            _imag[i] = _imag[j];
            _imag[j] = temp;
        }
    }
}

//////////////////////////////////////////////////////
// Reverse Bits
//////////////////////////////////////////////////////

uint16_t
FFTProcessorV2::reverseBits(
    uint16_t value,
    uint8_t bits
) const
{
    uint16_t result = 0;

    for (uint8_t i = 0; i < bits; i++)
    {
        result <<= 1;

        result |= (value & 1);

        value >>= 1;
    }

    return result;
}

//////////////////////////////////////////////////////
// FFT Engine
//////////////////////////////////////////////////////

void FFTProcessorV2::computeFFT()
{
    uint16_t fftSize =
        SignalBufferV2::shared().sampleCount();

    if (fftSize < 2)
    {
        return;
    }

    //--------------------------------------------------
    // Stage Loop
    //--------------------------------------------------

    uint16_t stage = 1;

    uint16_t size = 2;

    while (size <= fftSize)
    {
        butterflyStage(
            stage,
            size
        );

        stage++;

        size <<= 1;
    }
}

//////////////////////////////////////////////////////
// Butterfly Stage
//////////////////////////////////////////////////////

void FFTProcessorV2::butterflyStage(
    uint16_t stage,
    uint16_t fftSize
)
{
    //--------------------------------------------------
    // Half Size
    //--------------------------------------------------

    uint16_t half =
        fftSize >> 1;

    //--------------------------------------------------
    // Block Loop
    //--------------------------------------------------

    for
    (
        uint16_t block = 0;

        block < SignalBufferV2::shared().sampleCount();

        block += fftSize
    )
    {
        //--------------------------------------------------
        // Butterfly Loop
        //--------------------------------------------------

        for
        (
            uint16_t i = 0;

            i < half;

            i++
        )
        {
            //--------------------------------------------------
            // Next Part
            //--------------------------------------------------

            // Twiddle Factor

            // Butterfly Math

            // Complex Update
        }
    }
}