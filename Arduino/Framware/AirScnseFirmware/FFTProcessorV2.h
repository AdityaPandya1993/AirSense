//
//  FFTProcessorV2.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V2.2
//
//  Created by Aditya Pandya
//

#ifndef FFT_PROCESSOR_V2_H
#define FFT_PROCESSOR_V2_H

#include <Arduino.h>

class FFTProcessorV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static FFTProcessorV2& shared();

    //--------------------------------------------------
    // FFT
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    void printDebug() const;

    //--------------------------------------------------
    // Spectrum
    //--------------------------------------------------

    float magnitude(
        uint16_t index
    ) const;

    //--------------------------------------------------
    // Peak Information
    //--------------------------------------------------

    uint16_t peakIndex() const;

    float peakMagnitude() const;

    //--------------------------------------------------
    // Frequency
    //--------------------------------------------------

    float frequencyResolution() const;

    float frequencyAt(
        uint16_t index
    ) const;

private:

    FFTProcessorV2();

    //--------------------------------------------------
      // Internal
      //--------------------------------------------------

      void computeFFT();

      void computeMagnitude();

      void findPeak();

      // NEW
      void bitReverse();

      uint16_t reverseBits(
          uint16_t value,
          uint8_t bits
      ) const;

      void butterflyStage(
      uint16_t stage,
      uint16_t fftSize
      );

    //--------------------------------------------------
    // FFT Buffers
    //--------------------------------------------------

    static constexpr uint16_t MAX_SAMPLES = 256;

    float _real[MAX_SAMPLES];

    float _imag[MAX_SAMPLES];

    //--------------------------------------------------
    // Peak Cache
    //--------------------------------------------------

    uint16_t _peakIndex;

    float _peakMagnitude;
};

#endif