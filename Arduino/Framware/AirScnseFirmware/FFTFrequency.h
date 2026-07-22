//
//  FFTFrequency.h
//  AirSense Firmware
//

#ifndef FFT_FREQUENCY_H
#define FFT_FREQUENCY_H

#include <Arduino.h>

class FFTFrequency
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTFrequency& shared();

    //--------------------------------------------------
    // Update
    //--------------------------------------------------

    void update(
        uint16_t peakIndex,
        uint16_t fftSize,
        float sampleRate
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    float frequencyHz() const;

    float frequencyRPM() const;

    float frequencyBPM() const;

    float resolutionHz() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FFTFrequency();

private:

    float _frequencyHz;

    float _frequencyRPM;

    float _frequencyBPM;

    float _resolutionHz;
};

#endif