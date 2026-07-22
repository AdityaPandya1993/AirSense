//
//  FFTTwiddleTable.h
//  AirSense Firmware
//

#ifndef FFT_TWIDDLE_TABLE_H
#define FFT_TWIDDLE_TABLE_H

#include <Arduino.h>

class FFTTwiddleTable
{
public:

    static FFTTwiddleTable& shared();

    void initialize(uint16_t fftSize);

    float cosine(uint16_t index) const;

    float sine(uint16_t index) const;

private:

    FFTTwiddleTable();

    static constexpr uint16_t MAX_SIZE = 256;

    float _cos[MAX_SIZE / 2];

    float _sin[MAX_SIZE / 2];

    bool _initialized;
};

#endif