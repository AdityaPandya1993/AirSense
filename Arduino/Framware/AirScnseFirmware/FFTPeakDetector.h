//
//  FFTPeakDetector.h
//  AirSense Firmware
//

#ifndef FFT_PEAK_DETECTOR_H
#define FFT_PEAK_DETECTOR_H

#include <Arduino.h>

class FFTPeakDetector
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTPeakDetector& shared();

    //--------------------------------------------------
    // Analyze Spectrum
    //--------------------------------------------------

    void detect(
        const float* spectrum,
        uint16_t fftSize
    );

    //--------------------------------------------------
    // Peak
    //--------------------------------------------------

    uint16_t peakIndex() const;

    float peakMagnitude() const;

    //--------------------------------------------------
    // Second Peak
    //--------------------------------------------------

    uint16_t secondPeakIndex() const;

    float secondPeakMagnitude() const;

    //--------------------------------------------------
    // Noise Floor
    //--------------------------------------------------

    float noiseFloor() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    FFTPeakDetector();

private:

    uint16_t _peakIndex;
    float _peakMagnitude;

    uint16_t _secondPeakIndex;
    float _secondPeakMagnitude;

    float _noiseFloor;
};

#endif