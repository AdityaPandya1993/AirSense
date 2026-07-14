//
//  DSPPipeline.cpp
//  AirSense Firmware
//

#include "DSPPipeline.h"

#include "SignalProcessor.h"
#include "WindowFunction.h"
#include "FFTProcessor.h"
#include "PeakDetector.h"
#include "FrequencyAnalyzer.h"
#include "HeartEngine.h"
#include "BreathingEngine.h"

DSPPipeline&
DSPPipeline::shared()
{
    static DSPPipeline pipeline;

    return pipeline;
}

DSPPipeline::DSPPipeline()
{

}

void DSPPipeline::process(
    const CSIFrame& frame
)
{
    //--------------------------------------------------
    // Signal Processing
    //--------------------------------------------------

    SignalProcessor::shared()
        .process(frame);

    //--------------------------------------------------
    // Copy Breathing Signal
    //--------------------------------------------------

    float samples[128];

    for (int i = 0; i < 64; i++)
    {
        samples[i] =
            SignalProcessor::shared()
                .breathingSubcarrier(i);
    }

    for (int i = 64; i < 128; i++)
    {
        samples[i] = 0.0f;
    }

    //--------------------------------------------------
    // Window
    //--------------------------------------------------

    WindowFunction::shared()
        .apply(samples, 128);

    //--------------------------------------------------
    // FFT
    //--------------------------------------------------

    FFTProcessor::shared()
        .compute(samples, 128);

    //--------------------------------------------------
    // Copy Spectrum
    //--------------------------------------------------

    float spectrum[128];

    for (int i = 0; i < 128; i++)
    {
        spectrum[i] =
            FFTProcessor::shared()
                .magnitude(i);
    }

    //--------------------------------------------------
    // Peak Detection
    //--------------------------------------------------

    int peakIndex =
        PeakDetector::shared()
            .findPeak(
                spectrum,
                128
            );

    //--------------------------------------------------
    // Frequency
    //--------------------------------------------------

    float frequency =
        FrequencyAnalyzer::shared()
            .peakFrequency(
                peakIndex,
                128,
                20.0f
            );

    //--------------------------------------------------
    // Engines
    //--------------------------------------------------

    HeartEngine::shared()
        .update(frequency);

    BreathingEngine::shared()
        .update(frequency);
}