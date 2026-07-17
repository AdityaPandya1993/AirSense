//
//  DSPPipeline.cpp
//  AirSense Firmware
//
//  Version : 3.0
//

#include "DSPPipeline.h"

#include "CSIFrameBuffer.h"
#include "SubcarrierHistory.h"
#include "DSPConstants.h"
#include "SubcarrierSelector.h"
#include "SignalProcessor.h"
#include "EnergyAnalyzer.h"
#include "VarianceAnalyzer.h"
#include "QualityAnalyzer.h"
#include "MotionEnergyDetector.h"
#include "WindowFunction.h"
#include "FFTProcessor.h"
#include "PeakDetector.h"
#include "FrequencyAnalyzer.h"
#include "HeartEngine.h"
#include "BreathingEngine.h"
#include "ConfidenceEngine.h"
#include "DebugConsole.h"

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
    // Store Incoming Frame
    //--------------------------------------------------

    CSIFrameBuffer::shared().push(frame);

    //--------------------------------------------------
    // Wait Until Buffer Is Full
    //--------------------------------------------------

    if (!CSIFrameBuffer::shared().isFull())
    {
        return;
    }

    processBuffer();
}

void DSPPipeline::processBuffer()
{
    //--------------------------------------------------
    // Latest Frame
    //--------------------------------------------------

    const CSIFrame& latestFrame =
        CSIFrameBuffer::shared().frame(
            CSIFrameBuffer::shared().count() - 1
        );

    //--------------------------------------------------
    // Update History
    //--------------------------------------------------

    SubcarrierHistory::shared()
        .update(latestFrame);

    //--------------------------------------------------
    // Select Best Subcarrier
    //--------------------------------------------------

    SubcarrierSelector::shared()
        .analyze();

    int selectedSubcarrier =
        SubcarrierSelector::shared()
            .bestSubcarrier();

    (void)selectedSubcarrier;

    //--------------------------------------------------
    // Signal Processing
    //--------------------------------------------------

    SignalProcessor::shared()
        .process(latestFrame);

    //--------------------------------------------------
    // Prepare Samples
    //--------------------------------------------------

    float samples[DSP::FFTSize];

    //--------------------------------------------------
    // Version-1
    //
    // Currently processing every subcarrier.
    //
    // Version-2
    //
    // Process only selectedSubcarrier.
    //--------------------------------------------------

    for (int i = 0;
         i < DSP::SubcarrierCount;
         i++)
    {
        samples[i] =
            SignalProcessor::shared()
                .breathingSubcarrier(i);
    }

    for (int i = DSP::SubcarrierCount;
         i < DSP::FFTSize;
         i++)
    {
        samples[i] = 0.0f;
    }

    //--------------------------------------------------
    // Energy Analyzer
    //--------------------------------------------------

    EnergyAnalyzer::shared().update(
        samples,
        DSP::SubcarrierCount
    );

    //--------------------------------------------------
    // Variance Analyzer
    //--------------------------------------------------

    VarianceAnalyzer::shared().update(
        samples,
        DSP::SubcarrierCount
    );

    //--------------------------------------------------
    // Quality Analyzer
    //--------------------------------------------------

    QualityAnalyzer::shared().update(
        EnergyAnalyzer::shared().currentEnergy(),
        VarianceAnalyzer::shared().currentVariance()
    );

    //--------------------------------------------------
    // Motion Detector
    //--------------------------------------------------

    MotionEnergyDetector::shared().update(
        EnergyAnalyzer::shared().currentEnergy()
    );

    //--------------------------------------------------
    // Window Function
    //--------------------------------------------------

    WindowFunction::shared().apply(
        samples,
        DSP::FFTSize
    );

    //--------------------------------------------------
    // FFT
    //--------------------------------------------------

    FFTProcessor::shared().compute(
        samples,
        DSP::FFTSize
    );

    //--------------------------------------------------
    // FFT Spectrum
    //--------------------------------------------------

    float spectrum[DSP::FFTSize];

    for (int i = 0;
         i < DSP::FFTSize;
         i++)
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
                DSP::FFTSize
            );

    float peakValue =
        PeakDetector::shared()
            .peakValue();

    //--------------------------------------------------
    // Frequency Analysis
    //--------------------------------------------------

    float frequency =
        FrequencyAnalyzer::shared()
            .peakFrequency(
                peakIndex,
                DSP::FFTSize,
                DSP::SampleRate
            );

    //--------------------------------------------------
    // Update Heart Engine
    //--------------------------------------------------

    HeartEngine::shared()
        .update(
            frequency
        );

    //--------------------------------------------------
    // Update Breathing Engine
    //--------------------------------------------------

    BreathingEngine::shared()
        .update(
            frequency
        );
    //--------------------------------------------------
    // Confidence Engine
    //--------------------------------------------------

    ConfidenceEngine::shared().update(
        QualityAnalyzer::shared().currentQuality(),
        MotionEnergyDetector::shared().motionEnergy(),
        peakValue,
        VarianceAnalyzer::shared().currentVariance()
    );

    //--------------------------------------------------
    // Optional Debug Output
    //--------------------------------------------------
    // Uncomment if you want periodic DSP logging.
    //
    DebugConsole::shared().printDSP();
    //
    //--------------------------------------------------
}