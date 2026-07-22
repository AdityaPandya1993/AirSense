//
//  FFTButterflyV3.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "FFTButterflyV3.h"

#include <math.h>

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTButterflyV3&
FFTButterflyV3::shared()
{
    static FFTButterflyV3 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTButterflyV3::FFTButterflyV3()
{
    _ready = false;
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool FFTButterflyV3::begin()
{
    _ready = true;

    return true;
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void FFTButterflyV3::process(
    float* real,
    float* imag,
    uint16_t count
)
{
    if (!_ready)
    {
        return;
    }

    if (real == nullptr)
    {
        return;
    }

    if (imag == nullptr)
    {
        return;
    }

    if (count < 2)
    {
        return;
    }

    //--------------------------------------------------
    // Stage 1
    // Bit Reversal
    //--------------------------------------------------

    bitReverse(
        real,
        imag,
        count
    );

    //--------------------------------------------------
    // Stage 2
    // FFT Butterfly
    //--------------------------------------------------

    butterfly(
        real,
        imag,
        count
    );
}
////////////////////////////////////////////////////////
// Bit Reversal
////////////////////////////////////////////////////////

void FFTButterflyV3::bitReverse(
    float* real,
    float* imag,
    uint16_t count
)
{
    uint8_t bits = 0;

    uint16_t temp = count;

    while (temp > 1)
    {
        bits++;

        temp >>= 1;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        uint16_t j =
            reverseBits(
                i,
                bits
            );

        if (j > i)
        {
            //--------------------------------------------------
            // Swap Real
            //--------------------------------------------------

            float tempReal =
                real[i];

            real[i] =
                real[j];

            real[j] =
                tempReal;

            //--------------------------------------------------
            // Swap Imaginary
            //--------------------------------------------------

            float tempImag =
                imag[i];

            imag[i] =
                imag[j];

            imag[j] =
                tempImag;
        }
    }
}
////////////////////////////////////////////////////////
// Reverse Bits
////////////////////////////////////////////////////////

uint16_t FFTButterflyV3::reverseBits(
    uint16_t value,
    uint8_t bits
) const
{
    uint16_t reversed = 0;

    for (uint8_t i = 0; i < bits; i++)
    {
        reversed <<= 1;

        reversed |=
            (value & 1);

        value >>= 1;
    }

    return reversed;
}
////////////////////////////////////////////////////////
// FFT Butterfly
////////////////////////////////////////////////////////

void FFTButterflyV3::butterfly(
    float* real,
    float* imag,
    uint16_t count
)
{

const float PI = 3.14159265358979323846f;

    //--------------------------------------------------
    // FFT Stages
    //--------------------------------------------------

    for (uint16_t length = 2;
         length <= count;
         length <<= 1)
    {
        //--------------------------------------------------
        // Half Length
        //--------------------------------------------------

        uint16_t halfLength =
            length >> 1;

        //--------------------------------------------------
        // Angle
        //--------------------------------------------------

        float angle =
            -2.0f * PI / length;

        float wMulReal =
            cosf(angle);

        float wMulImag =
            sinf(angle);

        //--------------------------------------------------
        // Blocks
        //--------------------------------------------------

        for (uint16_t start = 0;
             start < count;
             start += length)
        {
            //--------------------------------------------------
            // Initial Rotation
            //--------------------------------------------------

            float wReal = 1.0f;
            float wImag = 0.0f;

            //--------------------------------------------------
            // Butterfly
            //--------------------------------------------------

            for (uint16_t j = 0;
                 j < halfLength;
                 j++)
            {
                uint16_t even =
                    start + j;

                uint16_t odd =
                    even + halfLength;

                //--------------------------------------------------
                // Complex Multiply
                //--------------------------------------------------

                float tempReal =
                    wReal * real[odd]
                    - wImag * imag[odd];

                float tempImag =
                    wReal * imag[odd]
                    + wImag * real[odd];

                //--------------------------------------------------
                // Butterfly
                //--------------------------------------------------

                real[odd] =
                    real[even] - tempReal;

                imag[odd] =
                    imag[even] - tempImag;

                real[even] +=
                    tempReal;

                imag[even] +=
                    tempImag;

                //--------------------------------------------------
                // Rotate W
                //--------------------------------------------------

                float nextReal =
                    wReal * wMulReal
                    - wImag * wMulImag;

                float nextImag =
                    wReal * wMulImag
                    + wImag * wMulReal;

                wReal = nextReal;
                wImag = nextImag;
            }
        }
    }
}