//
//  DSPPacketAnalyzerV3.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "DSPPacketAnalyzerV3.h"

#include "SignalBuffer.h"
#include "FFTWorkspace.h"

#include "DCRemovalV2.h"
#include "BandPassFilterV2.h"
#include "WindowFunctionV2.h"

#include "FFTButterflyV3.h"
#include "FFTMagnitudeV3.h"
#include "PeakDetectorV3.h"
#include "FrequencyAnalyzerV3.h"

#include "HeartRateEstimatorV3.h"
#include "BreathingEstimatorV3.h"
#include "ConfidenceEngineV3.h"

#include "DSPConfig.h"

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

DSPPacketAnalyzerV3&
DSPPacketAnalyzerV3::shared()
{
    static DSPPacketAnalyzerV3 instance;
    return instance;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

DSPPacketAnalyzerV3::DSPPacketAnalyzerV3()
{
    reset();

    _ready = false;
}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

bool DSPPacketAnalyzerV3::begin()
{
    FFTWorkspace::shared().begin();

    FFTButterflyV3::shared().begin();

    FFTMagnitudeV3::shared().begin();

    PeakDetectorV3::shared().begin();

    FrequencyAnalyzerV3::shared().begin();

    HeartRateEstimatorV3::shared().begin();

    BreathingEstimatorV3::shared().begin();

    ConfidenceEngineV3::shared().begin();

    _ready = true;

    return true;
}
////////////////////////////////////////////////////////
// Process
////////////////////////////////////////////////////////

void DSPPacketAnalyzerV3::process(
    const float* samples,
    uint16_t count
)
{
    //--------------------------------------------------
    // Validation
    //--------------------------------------------------

    if (!_ready)
    {
        return;
    }

    if (samples == nullptr)
    {
        return;
    }

    if (count == 0)
    {
        return;
    }

    //--------------------------------------------------
    // Limit Input Size
    //--------------------------------------------------

    if (count > DSPConfig::FFT_SIZE)
    {
        count = DSPConfig::FFT_SIZE;
    }

    //--------------------------------------------------
    // Store Raw Signal
    //--------------------------------------------------

    SignalBuffer::shared().update(
        samples,
        count
    );

    //--------------------------------------------------
    // Pre Processing
    //--------------------------------------------------

    DCRemovalV2::shared().process();

    BandPassFilterV2::shared().process();

    WindowFunctionV2::shared().process();

    //--------------------------------------------------
    // FFT Workspace
    //--------------------------------------------------

    float* real =
        FFTWorkspace::shared().real();

    float* imag =
        FFTWorkspace::shared().imag();

    float* magnitude =
        FFTWorkspace::shared().magnitude();
            //--------------------------------------------------
    // Copy Signal To FFT Workspace
    //--------------------------------------------------

    const float* signal =
        SignalBuffer::shared().samples();

    //--------------------------------------------------
    // Zero Padding
    //--------------------------------------------------

    for (uint16_t i = 0;
         i < DSPConfig::FFT_SIZE;
         i++)
    {
        if (i < count)
        {
            real[i] = signal[i];
        }
        else
        {
            real[i] = 0.0f;
        }

        imag[i] = 0.0f;
    }

    //--------------------------------------------------
    // Execute FFT
    //--------------------------------------------------

    FFTButterflyV3::shared().process(
        real,
        imag,
        DSPConfig::FFT_SIZE
    );

    //--------------------------------------------------
    // Magnitude Spectrum
    //--------------------------------------------------

    FFTMagnitudeV3::shared().process(
        real,
        imag,
        magnitude,
        DSPConfig::FFT_SIZE
    );
        //--------------------------------------------------
    // Peak Detection
    //--------------------------------------------------

    PeakDetectorV3::shared().process(
        magnitude,
        DSPConfig::FFT_SIZE
    );

    //--------------------------------------------------
    // Store Peak Results
    //--------------------------------------------------

    _dominantBin =
        PeakDetectorV3::shared().peakIndex();

    _peakMagnitude =
        PeakDetectorV3::shared().peakMagnitude();

    //--------------------------------------------------
    // Frequency Analysis
    //--------------------------------------------------

    FrequencyAnalyzerV3::shared().process(
        _dominantBin,
        _peakMagnitude,
        DSPConfig::FFT_SIZE,
        DSPConfig::SAMPLE_RATE
    );

    _dominantFrequency =
        FrequencyAnalyzerV3::shared().dominantFrequency();

    //--------------------------------------------------
    // Heart Rate Estimation
    //--------------------------------------------------

    HeartRateEstimatorV3::shared().process(
        _dominantFrequency
    );

    _heartRate =
        HeartRateEstimatorV3::shared().bpm();

    //--------------------------------------------------
    // Breathing Estimation
    //--------------------------------------------------

    BreathingEstimatorV3::shared().process(
        _dominantFrequency
    );

    _breathingRate =
        BreathingEstimatorV3::shared().breathingRate();

    //--------------------------------------------------
    // Confidence Engine
    //--------------------------------------------------

    ConfidenceEngineV3::shared().process(
        HeartRateEstimatorV3::shared().valid(),
        BreathingEstimatorV3::shared().valid(),
        _peakMagnitude
    );

    _confidence =
        ConfidenceEngineV3::shared().confidence();

    _detected =
        ConfidenceEngineV3::shared().detected();
            //--------------------------------------------------
    // Debug Output
    //--------------------------------------------------

    if (DSPConfig::PRINT_DSP)
    {
        Serial.println();

        Serial.println("========== DSP V3 ==========");

        Serial.print("FFT Size           : ");
        Serial.println(DSPConfig::FFT_SIZE);

        Serial.print("Sample Count       : ");
        Serial.println(count);

        Serial.print("Peak Bin           : ");
        Serial.println(_dominantBin);

        Serial.print("Peak Magnitude     : ");
        Serial.println(_peakMagnitude, 6);

        Serial.print("Dominant Frequency : ");
        Serial.print(_dominantFrequency, 4);
        Serial.println(" Hz");

        Serial.print("Heart Rate         : ");
        Serial.print(_heartRate, 2);
        Serial.println(" BPM");

        Serial.print("Breathing Rate     : ");
        Serial.print(_breathingRate, 2);
        Serial.println(" RPM");

        Serial.print("Confidence         : ");
        Serial.print(_confidence, 2);
        Serial.println(" %");

        Serial.print("Detected           : ");
        Serial.println(
            _detected
                ? "YES"
                : "NO"
        );

        Serial.println("============================");
        Serial.println();
    }
}