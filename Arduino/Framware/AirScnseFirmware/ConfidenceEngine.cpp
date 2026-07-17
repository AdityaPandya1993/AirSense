//
//  ConfidenceEngine.cpp
//  AirSense Firmware
//
//  Version : 1.0
//

#include "ConfidenceEngine.h"

ConfidenceEngine&
ConfidenceEngine::shared()
{
    static ConfidenceEngine engine;
    return engine;
}

ConfidenceEngine::ConfidenceEngine()
{
    _confidence = 0.0f;
}

void ConfidenceEngine::update(
    float quality,
    float motion,
    float peak,
    float variance
)
{
    //--------------------------------------------------
    // Clamp Inputs
    //--------------------------------------------------

    if (quality > 100.0f) quality = 100.0f;
    if (quality < 0.0f) quality = 0.0f;

    if (motion > 100.0f) motion = 100.0f;
    if (motion < 0.0f) motion = 0.0f;

    if (peak > 100.0f) peak = 100.0f;
    if (peak < 0.0f) peak = 0.0f;

    if (variance > 100.0f) variance = 100.0f;
    if (variance < 0.0f) variance = 0.0f;

    //--------------------------------------------------
    // Weighted Score
    //--------------------------------------------------

    _confidence =
          quality  * 0.35f
        + peak     * 0.30f
        + motion   * 0.20f
        + variance * 0.15f;

    //--------------------------------------------------
    // Final Clamp
    //--------------------------------------------------

    if (_confidence > 100.0f)
    {
        _confidence = 100.0f;
    }

    if (_confidence < 0.0f)
    {
        _confidence = 0.0f;
    }
}

float ConfidenceEngine::confidence() const
{
    return _confidence;
}