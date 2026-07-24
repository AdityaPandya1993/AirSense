#ifndef PACKET_FEATURE_EXTRACTOR_H
#define PACKET_FEATURE_EXTRACTOR_H

#include <Arduino.h>

class PacketFeatureExtractor
{
public:

    static PacketFeatureExtractor& shared();

    float extractAverageAmplitude(
        const float* amplitudes,
        uint16_t count
    );

private:

    PacketFeatureExtractor();
};

#endif