// //
// //  DSPPipelineV3.cpp
// //  AirSense Firmware
// //

// #include "DSPPipelineV3.h"

// #include "SignalBufferV3.h"
// #include "WindowFunctionV2.h"

// #include "FFTWorkspace.h"
// #include "FFTButterflyV3.h"
// #include "FFTMagnitudeV3.h"

// #include "PeakDetectorV3.h"
// #include "FrequencyAnalyzerV3.h"

// #include "HeartRateEstimatorV3.h"
// #include "BreathingEstimatorV3.h"
// #include "ConfidenceEngineV3.h"

// DSPPipelineV3&
// DSPPipelineV3::shared()
// {
//     static DSPPipelineV3 instance;

//     return instance;
// }

// DSPPipelineV3::DSPPipelineV3()
// {
//     reset();
// }

// bool DSPPipelineV3::begin()
// {
//     _ready = true;

//     SignalBufferV3::shared().begin();

//     FFTWorkspace::shared().begin();

//     FFTButterflyV3::shared().begin();

//     FFTMagnitudeV3::shared().begin();

//     PeakDetectorV3::shared().begin();

//     FrequencyAnalyzerV3::shared().begin();

//     HeartRateEstimatorV3::shared().begin();

//     BreathingEstimatorV3::shared().begin();

//     ConfidenceEngineV3::shared().begin();

//     return true;
// }

// void DSPPipelineV3::reset()
// {
//     _ready = false;
// }

// ////////////////////////////////////////////////////////
// // Process Complete DSP Pipeline
// ////////////////////////////////////////////////////////

// void DSPPipelineV3::process(
//     const float* samples,
//     uint16_t count,
//     float sampleRate
// )
// {
//     if (!_ready)
//     {
//         return;
//     }

//     //--------------------------------------------------
//     // Store Signal
//     //--------------------------------------------------

//     SignalBufferV3::shared().update(
//         samples,
//         count
//     );

//     //--------------------------------------------------
//     // Apply Window Function
//     //--------------------------------------------------

//     WindowFunctionV2::shared().process();

//     //--------------------------------------------------
//     // FFT Workspace
//     //--------------------------------------------------

//     float* real =
//         FFTWorkspace::shared().real();

//     float* imag =
//         FFTWorkspace::shared().imag();

//     float* magnitude =
//         FFTWorkspace::shared().magnitude();

//     //--------------------------------------------------
//     // Copy Signal -> FFT Input
//     //--------------------------------------------------

//     const float* signal =
//         SignalBufferV3::shared().samples();

//     for(uint16_t i = 0; i < count; i++)
//     {
//         real[i] = signal[i];

//         imag[i] = 0.0f;
//     }

//     //--------------------------------------------------
//     // Execute FFT
//     //--------------------------------------------------

//     FFTButterflyV3::shared().process(
//         real,
//         imag,
//         count
//     );

//     //--------------------------------------------------
//     // Magnitude Spectrum
//     //--------------------------------------------------

//     FFTMagnitudeV3::shared().process(
//         real,
//         imag,
//         magnitude,
//         count
//     );

//     //--------------------------------------------------
//     // Peak Detection
//     //--------------------------------------------------

//     PeakDetectorV3::shared().process(
//         magnitude,
//         count
//     );

//     //--------------------------------------------------
//     // Frequency Analysis
//     //--------------------------------------------------

//     FrequencyAnalyzerV3::shared().process(
//         PeakDetectorV3::shared().peakIndex(),
//         PeakDetectorV3::shared().peakMagnitude(),
//         count,
//         sampleRate
//     );

//     //--------------------------------------------------
//     // Heart Rate
//     //--------------------------------------------------

//     HeartRateEstimatorV3::shared().process(
//         FrequencyAnalyzerV3::shared().dominantFrequency()
//     );

//     //--------------------------------------------------
//     // Breathing Rate
//     //--------------------------------------------------

//     BreathingEstimatorV3::shared().process(
//         FrequencyAnalyzerV3::shared().dominantFrequency()
//     );

//     //--------------------------------------------------
//     // Confidence
//     //--------------------------------------------------

//     ConfidenceEngineV3::shared().process(
//         HeartRateEstimatorV3::shared().valid(),
//         BreathingEstimatorV3::shared().valid(),
//         PeakDetectorV3::shared().peakMagnitude()
//     );
// }
// ////////////////////////////////////////////////////////
// // Heart Rate
// ////////////////////////////////////////////////////////

// float
// DSPPipelineV3::heartRate() const
// {
//     return
//         HeartRateEstimatorV3
//             ::shared()
//             .bpm();
// }

// ////////////////////////////////////////////////////////
// // Breathing Rate
// ////////////////////////////////////////////////////////

// float
// DSPPipelineV3::breathingRate() const
// {
//     return
//         BreathingEstimatorV3
//             ::shared()
//             .breathingRate();
// }

// ////////////////////////////////////////////////////////
// // Confidence
// ////////////////////////////////////////////////////////

// float
// DSPPipelineV3::confidence() const
// {
//     return
//         ConfidenceEngineV3
//             ::shared()
//             .confidence();
// }

// ////////////////////////////////////////////////////////
// // Human Detection
// ////////////////////////////////////////////////////////

// bool
// DSPPipelineV3::humanDetected() const
// {
//     return
//         ConfidenceEngineV3
//             ::shared()
//             .detected();
// }