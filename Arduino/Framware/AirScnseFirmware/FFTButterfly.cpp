//
//  FFTButterfly.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.3
//

#include "FFTButterfly.h"
#include "FFTTwiddleGenerator.h"

FFTTwiddleGenerator&
twiddle =
    FFTTwiddleGenerator::shared();

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

FFTButterfly&
FFTButterfly::shared()
{
    static FFTButterfly instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

FFTButterfly::FFTButterfly()
{

}

////////////////////////////////////////////////////////
// Process Complete FFT
////////////////////////////////////////////////////////

void FFTButterfly::process(
    float* real,
    float* imag,
    uint16_t fftSize
)
{
    if (real == nullptr ||
        imag == nullptr)
    {
        return;
    }

    //--------------------------------------------------
    // Generate Twiddle Table
    //--------------------------------------------------

    twiddle.generate(
        fftSize
    );

    //--------------------------------------------------
    // FFT Stages
    //--------------------------------------------------

    uint16_t stageSize = 2;

    while (stageSize <= fftSize)
    {
        processStage(
            real,
            imag,
            fftSize,
            stageSize
        );

        stageSize <<= 1;
    }
}

////////////////////////////////////////////////////////
// One FFT Stage
////////////////////////////////////////////////////////

void FFTButterfly::processStage(
    float* real,
    float* imag,
    uint16_t fftSize,
    uint16_t stageSize
)
{
    uint16_t half =
        stageSize >> 1;

    uint16_t step =
        fftSize / stageSize;

    //--------------------------------------------------
    // Blocks
    //--------------------------------------------------

    for
    (
        uint16_t block = 0;

        block < fftSize;

        block += stageSize
    )
    {
        //--------------------------------------------------
        // Butterfly
        //--------------------------------------------------

        for
        (
            uint16_t i = 0;

            i < half;

            i++
        )
        {
            uint16_t index1 =
                block + i;

            uint16_t index2 =
                index1 + half;

            float wr =
                twiddle.cosine(
                    i * step
                );

            float wi =
                twiddle.sine(
                    i * step
                );

            butterfly(
                real,
                imag,
                index1,
                index2,
                wr,
                wi
            );
        }
    }
}

////////////////////////////////////////////////////////
// Butterfly
////////////////////////////////////////////////////////

void FFTButterfly::butterfly(
    float* real,
    float* imag,
    uint16_t index1,
    uint16_t index2,
    float wr,
    float wi
)
{
    //--------------------------------------------------
    // Complex Multiply
    //--------------------------------------------------

    float tr =
        wr * real[index2]
        -
        wi * imag[index2];

    float ti =
        wr * imag[index2]
        +
        wi * real[index2];

    //--------------------------------------------------
    // Save Upper
    //--------------------------------------------------

    float ur =
        real[index1];

    float ui =
        imag[index1];

    //--------------------------------------------------
    // Upper
    //--------------------------------------------------

    real[index1] =
        ur + tr;

    imag[index1] =
        ui + ti;

    //--------------------------------------------------
    // Lower
    //--------------------------------------------------

    real[index2] =
        ur - tr;

    imag[index2] =
        ui - ti;
}