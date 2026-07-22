//
//  FFTButterfly.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.3
//

#ifndef FFT_BUTTERFLY_H
#define FFT_BUTTERFLY_H

#include <Arduino.h>

class FFTButterfly
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTButterfly& shared();

    //--------------------------------------------------
    // Process Complete FFT
    //--------------------------------------------------

    void process(
        float* real,
        float* imag,
        uint16_t fftSize
    );

private:

    FFTButterfly();

    //--------------------------------------------------
    // One FFT Stage
    //--------------------------------------------------

    void processStage(
        float* real,
        float* imag,
        uint16_t fftSize,
        uint16_t stageSize
    );

    //--------------------------------------------------
    // One Butterfly
    //--------------------------------------------------

    void butterfly(
        float* real,
        float* imag,
        uint16_t index1,
        uint16_t index2,
        float twiddleReal,
        float twiddleImag
    );
};

#endif