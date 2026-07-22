//
//  DSPPipelineV2.cpp
//  AirSense Firmware
//

#include "DSPPipelineV2.h"

#include "SignalBufferV2.h"
#include "DCRemovalV2.h"
#include "BandPassFilterV2.h"
#include "WindowFunctionV2.h"

#include "FFTButterfly.h"
#include "FFTMagnitude.h"
#include "FFTPeakDetector.h"
#include "FFTFrequency.h"

#include "FrequencyAnalyzerV2.h"
#include "HeartEngineV2.h"
#include "BreathingEngineV2.h"
#include "ConfidenceEngineV2.h"
#include "HumanStateEngineV2.h"

#include "DSPConfig.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

DSPPipelineV2&
DSPPipelineV2::shared()
{
    static DSPPipelineV2 instance;

    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

DSPPipelineV2::DSPPipelineV2()
{

}

////////////////////////////////////////////////////////
// Reset
////////////////////////////////////////////////////////

void DSPPipelineV2::reset()
{
    SignalBufferV2::shared().reset();

    // DCRemovalV2::shared().reset();

    BandPassFilterV2::shared().reset();

    WindowFunctionV2::shared().reset();

    FFTMagnitude::shared().reset();

    FFTPeakDetector::shared().reset();

    FFTFrequency::shared().reset();

    FrequencyAnalyzerV2::shared().reset();

    HeartEngineV2::shared().reset();

    BreathingEngineV2::shared().reset();

    ConfidenceEngineV2::shared().reset();

    HumanStateEngineV2::shared().reset();
}

////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void DSPPipelineV2::process()
{
    preprocess();

    executeFFT();

    analyzeFrequency();

    analyzeVitals();

    updateConfidence();

    updateHumanState();
}

////////////////////////////////////////////////////////
// Preprocess
////////////////////////////////////////////////////////

void DSPPipelineV2::preprocess()
{
    //--------------------------------------------------
    // Get Signal Buffer
    //--------------------------------------------------

    float* samples =
    SignalBufferV2::shared().workingSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (samples == nullptr || count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // DC Removal
    //--------------------------------------------------

    DCRemovalV2::shared().process();

    //--------------------------------------------------
    // Band Pass Filter
    //--------------------------------------------------

    BandPassFilterV2::shared().process();

    //--------------------------------------------------
    // Window Function
    //--------------------------------------------------

    WindowFunctionV2::shared().process();
}

////////////////////////////////////////////////////////
// Execute FFT
////////////////////////////////////////////////////////

void DSPPipelineV2::executeFFT()
{
    //--------------------------------------------------
    // Get Samples
    //--------------------------------------------------

    float* real =
    SignalBufferV2::shared().fftSamples();

    uint16_t count =
        SignalBufferV2::shared().sampleCount();

    if (real == nullptr || count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Temporary Imaginary Buffer
    //--------------------------------------------------

    static float imag[DSPConfig::FFT_SIZE];

    for (uint16_t i = 0; i < count; i++)
    {
        imag[i] = 0.0f;
    }

    //--------------------------------------------------
    // FFT Butterfly
    //--------------------------------------------------

    FFTButterfly::shared().process(
        real,
        imag,
        count
    );

    //--------------------------------------------------
    // Magnitude Spectrum
    //--------------------------------------------------

    FFTMagnitude::shared().compute(
        real,
        imag,
        count
    );

    //--------------------------------------------------
    // Peak Detection
    //--------------------------------------------------

    FFTPeakDetector::shared().detect(
        FFTMagnitude::shared().spectrum(),
        count
    );

    //--------------------------------------------------
    // Frequency Calculation
    //--------------------------------------------------

    FFTFrequency::shared().update(
        FFTPeakDetector::shared().peakIndex(),
        count,
        DSPConfig::SAMPLE_RATE
    );
}

////////////////////////////////////////////////////////
// Analyze Frequency
////////////////////////////////////////////////////////

void DSPPipelineV2::analyzeFrequency()
{
    //--------------------------------------------------
    // Analyze Spectrum
    //--------------------------------------------------

    FrequencyAnalyzerV2::shared().analyze(
        FFTMagnitude::shared().spectrum(),
        SignalBufferV2::shared().sampleCount(),
        DSPConfig::SAMPLE_RATE
    );

    //--------------------------------------------------
    // Update Heart Engine
    //--------------------------------------------------

    HeartEngineV2::shared().update(
        FrequencyAnalyzerV2::shared().heartBPM(),
        FrequencyAnalyzerV2::shared().confidence()
    );

    //--------------------------------------------------
    // Update Breathing Engine
    //--------------------------------------------------

    BreathingEngineV2::shared().update(
        FrequencyAnalyzerV2::shared().breathingRPM(),
        FrequencyAnalyzerV2::shared().confidence()
    );
}

////////////////////////////////////////////////////////
// Analyze Vitals
////////////////////////////////////////////////////////

void DSPPipelineV2::analyzeVitals()
{
    //--------------------------------------------------
    // Reserved
    //
    // Future Modules:
    //  • HRV Engine
    //  • Respiration Variability
    //  • Arrhythmia Detection
    //  • Sleep Detection
    //  • Motion Classification
    //--------------------------------------------------
}

////////////////////////////////////////////////////////
// Update Confidence
////////////////////////////////////////////////////////

void DSPPipelineV2::updateConfidence()
{
    //--------------------------------------------------
    // FFT Peak
    //--------------------------------------------------

    float peak =
        FFTPeakDetector::shared().peakMagnitude();

    //--------------------------------------------------
    // Noise Floor
    //--------------------------------------------------

    float noise =
        FFTPeakDetector::shared().noiseFloor();

    //--------------------------------------------------
    // Heart Confidence
    //--------------------------------------------------

    float heartConfidence =
        HeartEngineV2::shared().confidence();

    //--------------------------------------------------
    // Breathing Confidence
    //--------------------------------------------------

    float breathingConfidence =
        BreathingEngineV2::shared().confidence();

    //--------------------------------------------------
    // Signal Quality
    //--------------------------------------------------

    float signalQuality = 1.0f;

    //--------------------------------------------------
    // Motion
    //--------------------------------------------------

    bool motionDetected = false;

    //--------------------------------------------------
    // Update Confidence Engine
    //--------------------------------------------------

    ConfidenceEngineV2::shared().update(
        peak,
        noise,
        heartConfidence,
        breathingConfidence,
        signalQuality,
        motionDetected
    );
}

////////////////////////////////////////////////////////
// Update Human State
////////////////////////////////////////////////////////

void DSPPipelineV2::updateHumanState()
{
    //--------------------------------------------------
    // Motion (Placeholder)
    //--------------------------------------------------

    bool motionDetected = false;

    //--------------------------------------------------
    // Heart
    //--------------------------------------------------

    float heart =
        HeartEngineV2::shared().filteredBPM();

    //--------------------------------------------------
    // Breathing
    //--------------------------------------------------

    float breathing =
        BreathingEngineV2::shared().filteredRPM();

    //--------------------------------------------------
    // Confidence
    //--------------------------------------------------

    float confidence =
        ConfidenceEngineV2::shared().confidence();

    //--------------------------------------------------
    // Signal Quality
    //--------------------------------------------------

    float signalQuality = 1.0f;

    //--------------------------------------------------
    // Update Human State
    //--------------------------------------------------

    HumanStateEngineV2::shared().update(
        motionDetected,
        heart,
        breathing,
        confidence,
        signalQuality
    );
}