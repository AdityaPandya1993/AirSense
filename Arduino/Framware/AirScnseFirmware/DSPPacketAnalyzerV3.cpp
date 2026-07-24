//
//  DSPPacketAnalyzerV3.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V4
//

#include "DSPPacketAnalyzerV3.h"

#include "SignalBufferV2.h"
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

#include "CircularSignalBuffer.h"
#include "PacketFeatureExtractor.h"
#include "VitalSignalExtractor.h"

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

    VitalSignalExtractor::shared().begin();

    ConfidenceEngineV3::shared().begin();

    CircularSignalBuffer::shared().begin();

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
    // Performance Counter
    //--------------------------------------------------

    static uint32_t dspCounter = 0;
    static uint32_t dspTimer = millis();

    dspCounter++;

    if (millis() - dspTimer >= 1000)
    {
        Serial.print("DSP/sec : ");
        Serial.println(dspCounter);

        dspCounter = 0;

        dspTimer = millis();
    }

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

    if (count > DSPConfig::FFT_SIZE)
    {
        count = DSPConfig::FFT_SIZE;
    }

    //--------------------------------------------------
    // Convert Current CSI Packet
    // -> Single Feature
    //--------------------------------------------------

    float packetValue =
        PacketFeatureExtractor::shared()
            .extractAverageAmplitude(
                samples,
                count
            );

    //--------------------------------------------------
    // Push Feature Into Circular Buffer
    //--------------------------------------------------

    CircularSignalBuffer::shared().push(
        &packetValue,
        1
    );

    //--------------------------------------------------
    // Debug
    //--------------------------------------------------

    static uint32_t bufferTimer = millis();

    if (millis() - bufferTimer >= 1000)
    {
        bufferTimer = millis();

        Serial.print("Buffer Samples : ");

        Serial.println(
            CircularSignalBuffer::shared().totalSamples()
        );
    }

    //--------------------------------------------------
    // Wait Until FFT Buffer Full
    //--------------------------------------------------

    if (!CircularSignalBuffer::shared().ready())
    {
        return;
    }

    Serial.println();
    Serial.println("==================================");
    Serial.println(" FFT BUFFER READY ");
    Serial.println("==================================");

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
    // Copy Circular Buffer -> SignalBufferV2
    //--------------------------------------------------

    const float* signal =
        CircularSignalBuffer::shared().data();

    SignalBufferV2::shared().updateRaw(
        signal,
        DSPConfig::FFT_SIZE
    );

    SignalBufferV2::shared().copyRawToWorking();
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

    SignalBufferV2::shared().copyWorkingToFFT();

    //--------------------------------------------------
    // FFT
    //--------------------------------------------------

    float* fft =
        SignalBufferV2::shared().fftSamples();

    for(uint16_t i = 0; i < DSPConfig::FFT_SIZE; i++)
    {
        real[i] = fft[i];
        imag[i] = 0.0f;
    }

    FFTButterflyV3::shared().process(
        real,
        imag,
        DSPConfig::FFT_SIZE
    );

    //--------------------------------------------------
    // FFT Magnitude
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

    Serial.println();
    Serial.println("========== FFT RESULT ==========");

    Serial.print("Peak Bin : ");
    Serial.println(_dominantBin);

    Serial.print("Peak Magnitude : ");
    Serial.println(_peakMagnitude, 6);

    Serial.print("Dominant Frequency : ");
    Serial.print(_dominantFrequency, 4);
    Serial.println(" Hz");

    Serial.println("===============================");
        //--------------------------------------------------
    // Heart Rate Estimation
    //--------------------------------------------------

    HeartRateEstimatorV3::shared().process(
        _dominantFrequency
    );

    _heartRate =
        HeartRateEstimatorV3::shared().bpm();

    //--------------------------------------------------
    // Breathing Rate Estimation
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
    // DSP Debug
    //--------------------------------------------------

    if (DSPConfig::PRINT_DSP)
    {
        Serial.println();

        Serial.println("========== DSP V4 ==========");

        Serial.print("Heart Rate : ");
        Serial.print(_heartRate, 2);
        Serial.println(" BPM");

        Serial.print("Breathing : ");
        Serial.print(_breathingRate, 2);
        Serial.println(" RPM");

        Serial.print("Confidence : ");
        Serial.print(_confidence, 2);
        Serial.println(" %");

        Serial.print("Detected : ");
        Serial.println(
            _detected
                ? "YES"
                : "NO"
        );

        Serial.println("============================");
        Serial.println();
    }
}