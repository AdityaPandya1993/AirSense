//
//  DSPPacketAnalyzerV3.h
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#ifndef DSP_PACKET_ANALYZER_V3_H
#define DSP_PACKET_ANALYZER_V3_H

#include <Arduino.h>

class DSPPacketAnalyzerV3
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static DSPPacketAnalyzerV3& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    bool begin();

    //--------------------------------------------------
    // Process One CSI Frame
    //--------------------------------------------------

    void process(
        const float* samples,
        uint16_t count
    );

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    bool detected() const;

    float heartRate() const;

    float breathingRate() const;

    float confidence() const;

    float dominantFrequency() const;

    uint16_t dominantBin() const;

    float peakMagnitude() const;

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    DSPPacketAnalyzerV3();

private:

    bool _ready;

    bool _detected;

    float _heartRate;

    float _breathingRate;

    float _confidence;

    float _dominantFrequency;

    uint16_t _dominantBin;

    float _peakMagnitude;
};

#endif