#include "PacketFeatureExtractor.h"
#include "VitalSignalExtractor.h"

PacketFeatureExtractor&
PacketFeatureExtractor::shared()
{
    static PacketFeatureExtractor instance;

    return instance;
}

PacketFeatureExtractor::PacketFeatureExtractor()
{
}

float PacketFeatureExtractor::extractAverageAmplitude(
    const float* amplitudes,
    uint16_t count
)
{
    return VitalSignalExtractor::shared().process(
        amplitudes,
        count
    );
}