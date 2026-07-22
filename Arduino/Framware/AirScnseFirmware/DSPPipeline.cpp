//
//  DSPPipeline.cpp
//  AirSense Firmware
//
//  Version : 4.0
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

#include "BandPassFilter.h"

#include "WindowFunction.h"
#include "FFTProcessor.h"

#include "PeakDetector.h"
#include "FrequencyAnalyzer.h"

#include "HeartEngine.h"
#include "BreathingEngine.h"

#include "ConfidenceEngine.h"

#include "DebugConsole.h"
#include "SignalBuffer.h"

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
    // Push Latest Frame
    //--------------------------------------------------

    CSIFrameBuffer::shared().push(
        frame
    );

    //--------------------------------------------------
    // Wait Until Buffer Is Full
    //--------------------------------------------------

    if (!CSIFrameBuffer::shared().isFull())
    {
        return;
    }

    //--------------------------------------------------
    // Process Complete Buffer
    //--------------------------------------------------

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
    // Update Subcarrier History
    //--------------------------------------------------

    SubcarrierHistory::shared().update(
        latestFrame
    );

    //--------------------------------------------------
    // Select Best Subcarrier
    //--------------------------------------------------

    SubcarrierSelector::shared().analyze();

    int selectedSubcarrier =
        SubcarrierSelector::shared()
            .bestSubcarrier();

    (void)selectedSubcarrier;

    //--------------------------------------------------
    // Signal Processing
    //--------------------------------------------------

    SignalProcessor::shared().process(
        latestFrame
    );

   //--------------------------------------------------
// Prepare Signal Buffer
//--------------------------------------------------

float samples[DSP::FFTSize];

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
// Update Shared Signal Buffer
//--------------------------------------------------

SignalBuffer::shared().update(
    samples,
    DSP::FFTSize
);

    //--------------------------------------------------
    // Energy Analyzer
    //--------------------------------------------------

    EnergyAnalyzer::shared().update(
    SignalBuffer::shared().samples(),
    SignalBuffer::shared().sampleCount()
);

    //--------------------------------------------------
    // Variance Analyzer
    //--------------------------------------------------

    VarianceAnalyzer::shared().update(
    SignalBuffer::shared().samples(),
    SignalBuffer::shared().sampleCount()
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
    // Band Pass Filter
    //--------------------------------------------------

    BandPassFilter::shared().process();

    WindowFunction::shared().process();

FFTProcessor::shared().compute(
    const_cast<float*>(
        SignalBuffer::shared().samples()
    ),
    SignalBuffer::shared().sampleCount()
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
        PeakDetector::shared().findPeak(
            spectrum,
            DSP::FFTSize
        );

    float peakValue =
        PeakDetector::shared().peakValue();

    //--------------------------------------------------
    // Frequency Analysis
    //--------------------------------------------------

    float frequency =
        FrequencyAnalyzer::shared().peakFrequency(
            peakIndex,
            DSP::FFTSize,
            DSP::SampleRate
        );

    //--------------------------------------------------
    // Heart Engine
    //--------------------------------------------------

    HeartEngine::shared().update(
        frequency
    );

    //--------------------------------------------------
    // Breathing Engine
    //--------------------------------------------------

    BreathingEngine::shared().update(
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
    // Debug Console
    //--------------------------------------------------

    DebugConsole::shared().printDSP();
}