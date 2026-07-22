//
//  ConfidenceEngineV2.cpp
//  AirSense Firmware
//

#include "ConfidenceEngineV2.h"

ConfidenceEngineV2&
ConfidenceEngineV2::shared()
{
    static ConfidenceEngineV2 instance;

    return instance;
}

////////////////////////////////////////////////////////

ConfidenceEngineV2::ConfidenceEngineV2()
{
    reset();
}

////////////////////////////////////////////////////////

void ConfidenceEngineV2::reset()
{
    _confidence = 0.0f;

    _confidencePercent = 0;

    _reliable = false;
}

////////////////////////////////////////////////////////

void ConfidenceEngineV2::update(
    float fftPeak,
    float noiseFloor,
    float heartConfidence,
    float breathingConfidence,
    float signalQuality,
    bool motionDetected
)
{
    //--------------------------------------------------
    // Peak vs Noise
    //--------------------------------------------------

    float snrScore = 0.0f;

    if (fftPeak > noiseFloor && fftPeak > 0.0f)
    {
        snrScore =
            (fftPeak - noiseFloor) /
            fftPeak;

        if (snrScore > 1.0f)
        {
            snrScore = 1.0f;
        }
    }

    //--------------------------------------------------
    // Motion Penalty
    //--------------------------------------------------

    float motionScore =
        motionDetected ? 0.40f : 1.00f;

    //--------------------------------------------------
    // Final Score
    //--------------------------------------------------

    _confidence =
        (
            snrScore * 0.35f +
            heartConfidence * 0.25f +
            breathingConfidence * 0.25f +
            signalQuality * 0.15f
        ) * motionScore;

    //--------------------------------------------------
    // Clamp
    //--------------------------------------------------

    if (_confidence < 0.0f)
    {
        _confidence = 0.0f;
    }

    if (_confidence > 1.0f)
    {
        _confidence = 1.0f;
    }

    //--------------------------------------------------
    // Percent
    //--------------------------------------------------

    _confidencePercent =
        (uint8_t)(_confidence * 100.0f);

    //--------------------------------------------------
    // Reliable?
    //--------------------------------------------------

    _reliable =
        (_confidence >= 0.70f);
}

////////////////////////////////////////////////////////

float ConfidenceEngineV2::confidence() const
{
    return _confidence;
}

////////////////////////////////////////////////////////

uint8_t ConfidenceEngineV2::confidencePercent() const
{
    return _confidencePercent;
}

////////////////////////////////////////////////////////

bool ConfidenceEngineV2::isReliable() const
{
    return _reliable;
}