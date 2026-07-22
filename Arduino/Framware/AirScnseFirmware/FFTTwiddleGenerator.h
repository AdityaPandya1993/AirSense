//
//  FFTTwiddleGenerator.h
//  AirSense Firmware
//

#ifndef FFT_TWIDDLE_GENERATOR_H
#define FFT_TWIDDLE_GENERATOR_H

#include <Arduino.h>

class FFTTwiddleGenerator
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTTwiddleGenerator& shared();

    //--------------------------------------------------
    // Generate Lookup Table
    //--------------------------------------------------

    void generate(
        uint16_t fftSize
    );

    //--------------------------------------------------
    // Lookup
    //--------------------------------------------------

    float cosine(
        uint16_t index
    ) const;

    float sine(
        uint16_t index
    ) const;

    //--------------------------------------------------
    // Utilities
    //--------------------------------------------------

    uint16_t size() const;

    void reset();

private:

    FFTTwiddleGenerator();

private:

    static constexpr uint16_t MAX_SIZE = 256;

    float _cosTable[MAX_SIZE / 2];

    float _sinTable[MAX_SIZE / 2];

    uint16_t _fftSize;

    bool _generated;
};

#endif