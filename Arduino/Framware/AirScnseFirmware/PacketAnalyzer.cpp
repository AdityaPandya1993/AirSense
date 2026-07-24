//
//  PacketAnalyzer.cpp
//  AirSense Firmware
//
//  AirSense DSP Refactor V3
//

#include "PacketAnalyzer.h"

#include "IQDecoder.h"
#include "CSIConverter.h"

#include "DCRemoval.h"
#include "LowPassFilter.h"

#include "MotionEnergy.h"
#include "MotionEnergyFilter.h"

#include "HumanStateMachine.h"

#include "DSPPacketAnalyzerV3.h"

#include "DSPConfig.h"

#include "DeviceController.h"
#include "HumanEntity.h"

#include <math.h>

////////////////////////////////////////////////////////
// State -> Motion String
////////////////////////////////////////////////////////

static String motionStringForState(HumanState state)
{
    switch (state)
    {
        case HumanState::Booting:         return "Booting";
        case HumanState::Idle:            return "Idle";
        case HumanState::PersonDetected:  return "Detected";
        case HumanState::Still:           return "Still";
        case HumanState::Monitoring:      return "Monitoring";
        case HumanState::Walking:         return "Walking";
        case HumanState::Running:         return "Running";
        case HumanState::GestureDetected: return "Gesture";
        case HumanState::FallDetected:    return "Falling";
        case HumanState::Alert:           return "Alert";
    }

    return "Unknown";
}

////////////////////////////////////////////////////////
// DSP Temporary Buffer
////////////////////////////////////////////////////////

static float dspAmplitudeBuffer[DSPConfig::FFT_SIZE];

////////////////////////////////////////////////////////
// Singleton
////////////////////////////////////////////////////////

PacketAnalyzer&
PacketAnalyzer::shared()
{
    static PacketAnalyzer analyzer;

    return analyzer;
}

////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////

PacketAnalyzer::PacketAnalyzer()
{

}

////////////////////////////////////////////////////////
// Begin
////////////////////////////////////////////////////////

void PacketAnalyzer::begin()
{
    Serial.println();

    Serial.println("========================================");
    Serial.println("     AirSense Packet Analyzer Ready");
    Serial.println("========================================");

    static uint32_t analyzerCounter = 0;
    static uint32_t analyzerTime = millis();

    analyzerCounter++;

    if (millis() - analyzerTime > 1000)
    {
        Serial.print("Analyzer/sec : ");
        Serial.println(analyzerCounter);

        analyzerCounter = 0;

        analyzerTime = millis();
    }

    //--------------------------------------------------
    // Initialize DSP V3
    //--------------------------------------------------

    DSPPacketAnalyzerV3::shared().begin();

    Serial.println("DSP Pipeline V3 Ready");

    Serial.println("========================================");
}

////////////////////////////////////////////////////////
// Analyze
////////////////////////////////////////////////////////

void PacketAnalyzer::analyze(
    const RawCSIFrame& frame
)
{
    //--------------------------------------------------
    // IQ Decoder
    //--------------------------------------------------

    IQDecoder::shared().decode(
        frame
    );

    //--------------------------------------------------
    // CSI Converter
    //--------------------------------------------------

    CSIConverter::shared().convert(
        IQDecoder::shared().samples(),
        IQDecoder::shared().sampleCount()
    );

    //--------------------------------------------------
    // DC Removal
    //--------------------------------------------------

    DCRemoval::shared().remove(
        CSIConverter::shared().samples(),
        CSIConverter::shared().sampleCount()
    );

    //--------------------------------------------------
    // Low Pass Filter
    //--------------------------------------------------

    LowPassFilter::shared().filter(
        DCRemoval::shared().samples(),
        DCRemoval::shared().sampleCount()
    );

    //--------------------------------------------------
    // Prepare DSP Buffer
    //--------------------------------------------------

    uint16_t count =
        LowPassFilter::shared().sampleCount();

    const FilteredSample* filtered =
        LowPassFilter::shared().samples();

    if (count > DSPConfig::FFT_SIZE)
    {
        count = DSPConfig::FFT_SIZE;
    }

    for (uint16_t i = 0; i < count; i++)
    {
        dspAmplitudeBuffer[i] =
            filtered[i].amplitude;
    }

    //--------------------------------------------------
    // Execute DSP Pipeline V3
    //--------------------------------------------------

    DSPPacketAnalyzerV3::shared().process(
        dspAmplitudeBuffer,
        count
    );

        //--------------------------------------------------
    // Motion Energy
    //--------------------------------------------------

    MotionEnergy::shared().calculate(
        LowPassFilter::shared().samples(),
        LowPassFilter::shared().sampleCount()
    );

    //--------------------------------------------------
    // Motion Energy Filter
    //--------------------------------------------------

    MotionEnergyFilter::shared().filter(
        MotionEnergy::shared().energy()
    );

    //--------------------------------------------------
    // Human State Machine
    //--------------------------------------------------

    bool personDetected =
        DSPPacketAnalyzerV3::shared().detected();

    HumanStateMachine::shared().update(
        personDetected,
        MotionEnergyFilter::shared().energy()
    );

    //--------------------------------------------------
    // Push Real Results To Device Controller
    //--------------------------------------------------

    HumanEntity human;

    human.state = HumanStateMachine::shared().currentState();
    human.detected = personDetected;
    human.personCount = personDetected ? 1 : 0;
    human.motion = motionStringForState(human.state);
    human.heartRate = (int)roundf(DSPPacketAnalyzerV3::shared().heartRate());
    human.breathing = (int)roundf(DSPPacketAnalyzerV3::shared().breathingRate());

    // No real spatial tracking wired up yet, so position stays at origin.
    human.x = 0.0f;
    human.y = 0.0f;

    DeviceController::shared().updateHuman(human);

    //--------------------------------------------------
    // Print Packet Information
    //--------------------------------------------------

    printHeader();

    printSummary(
        frame
    );

    printSignedSamples(
        frame,
        12,
        32
    );

    printIQPairs(
        frame,
        12,
        16
    );

    printCSISamples(
        CSIConverter::shared().samples(),
        CSIConverter::shared().sampleCount()
    );

    printCenteredSamples(
        CSIConverter::shared().samples(),
        DCRemoval::shared().samples(),
        DCRemoval::shared().sampleCount(),
        DCRemoval::shared().meanAmplitude()
    );

    printFilteredSamples(
        DCRemoval::shared().samples(),
        LowPassFilter::shared().samples(),
        LowPassFilter::shared().sampleCount()
    );

    printMotionEnergyFilter(
        MotionEnergy::shared().energy(),
        MotionEnergyFilter::shared().energy()
    );

    printHumanState();
}
////////////////////////////////////////////////////////
// Header
////////////////////////////////////////////////////////

void PacketAnalyzer::printHeader() const
{
    Serial.println();

    Serial.println("========================================");
    Serial.println("        AirSense Packet Analyzer");
    Serial.println("========================================");
}

////////////////////////////////////////////////////////
// Summary
////////////////////////////////////////////////////////

void PacketAnalyzer::printSummary(
    const RawCSIFrame& frame
) const
{
    Serial.print("Timestamp          : ");
    Serial.println(frame.timestamp);

    Serial.print("RSSI               : ");
    Serial.println(frame.rssi);

    Serial.print("Channel            : ");
    Serial.println(frame.channel);

    Serial.print("Packet Length      : ");
    Serial.println(frame.length);

    Serial.print("First Word Invalid : ");

    Serial.println(
        frame.firstWordInvalid
            ? "YES"
            : "NO"
    );

    Serial.println("----------------------------------------");
}

////////////////////////////////////////////////////////
// Raw Signed Values
////////////////////////////////////////////////////////

void PacketAnalyzer::printSignedSamples(
    const RawCSIFrame& frame,
    uint16_t startOffset,
    uint16_t sampleCount
) const
{
    Serial.println("SIGNED VALUES");
    Serial.println();

    for (uint16_t i = 0; i < sampleCount; i++)
    {
        if ((startOffset + i) >= frame.length)
        {
            break;
        }

        Serial.print(
            (int8_t)frame.data[startOffset + i]
        );

        Serial.print('\t');

        if ((i + 1) % 8 == 0)
        {
            Serial.println();
        }
    }

    Serial.println();
    Serial.println("----------------------------------------");
}
////////////////////////////////////////////////////////
// IQ Samples
////////////////////////////////////////////////////////

void PacketAnalyzer::printIQPairs(
    const RawCSIFrame& frame,
    uint16_t startOffset,
    uint16_t pairCount
) const
{
    Serial.println("I/Q PAIRS");
    Serial.println();

    Serial.println("Index\tI\tQ");

    for (uint16_t i = 0; i < pairCount; i++)
    {
        uint16_t index =
            startOffset + (i * 2);

        if ((index + 1) >= frame.length)
        {
            break;
        }

        int8_t iValue =
            frame.data[index];

        int8_t qValue =
            frame.data[index + 1];

        Serial.print(i);
        Serial.print('\t');

        Serial.print(iValue);
        Serial.print('\t');

        Serial.println(qValue);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}

////////////////////////////////////////////////////////
// CSI Samples
////////////////////////////////////////////////////////

void PacketAnalyzer::printCSISamples(
    const CSISample* samples,
    uint16_t count
) const
{
    Serial.println("CSI CONVERTER OUTPUT");
    Serial.println();

    Serial.println("Idx\tAmplitude\tPhase");

    uint16_t maxSamples =
        min<uint16_t>(count, 16);

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(i);
        Serial.print('\t');

        Serial.print(samples[i].amplitude, 4);

        Serial.print("\t\t");

        Serial.println(samples[i].phase, 4);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}
//--------------------------------------------------
// DC Removal
//--------------------------------------------------

void PacketAnalyzer::printCenteredSamples(
    const CSISample* original,
    const CenteredSample* centered,
    uint16_t count,
    float mean
) const
{
    Serial.println("DC REMOVAL OUTPUT");
    Serial.println();

    Serial.print("Mean Amplitude : ");
    Serial.println(mean, 4);
    Serial.println();

    Serial.println("Idx\tOriginal\tCentered");

    uint16_t maxSamples =
        min<uint16_t>(count, 16);

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(i);
        Serial.print('\t');

        Serial.print(original[i].amplitude, 4);

        Serial.print("\t\t");

        Serial.println(centered[i].amplitude, 4);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}
//--------------------------------------------------
// Low Pass Filter
//--------------------------------------------------

void PacketAnalyzer::printFilteredSamples(
    const CenteredSample* original,
    const FilteredSample* filtered,
    uint16_t count
) const
{
    Serial.println("LOW PASS FILTER OUTPUT");
    Serial.println();

    Serial.println("Idx\tCentered\tFiltered");

    uint16_t maxSamples =
        min<uint16_t>(count, 16);

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(i);
        Serial.print('\t');

        Serial.print(original[i].amplitude, 4);

        Serial.print("\t\t");

        Serial.println(filtered[i].amplitude, 4);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}
//--------------------------------------------------
// Motion Energy
//--------------------------------------------------

void PacketAnalyzer::printMotionEnergyFilter(
    float rawEnergy,
    float filteredEnergy
) const
{
    Serial.println("MOTION ENERGY");
    Serial.println();

    Serial.print("Raw Energy      : ");
    Serial.println(rawEnergy, 6);

    Serial.print("Filtered Energy : ");
    Serial.println(filteredEnergy, 6);

    Serial.println();

    Serial.print("Motion State    : ");

    if (filteredEnergy < 0.02f)
    {
        Serial.println("Still");
    }
    else if (filteredEnergy < 0.20f)
    {
        Serial.println("Monitoring");
    }
    else if (filteredEnergy < 1.00f)
    {
        Serial.println("Walking");
    }
    else if (filteredEnergy < 3.00f)
    {
        Serial.println("Running");
    }
    else
    {
        Serial.println("Alert");
    }

    Serial.println();

    //--------------------------------------------------
    // DSP V3 Result
    //--------------------------------------------------

    Serial.println("----------- DSP V3 -----------");

    Serial.print("Detected       : ");
    Serial.println(
        DSPPacketAnalyzerV3::shared().detected()
            ? "YES"
            : "NO"
    );

    Serial.print("Heart Rate     : ");
    Serial.print(
        DSPPacketAnalyzerV3::shared().heartRate(),
        2
    );
    Serial.println(" BPM");

    Serial.print("Breathing Rate : ");
    Serial.print(
        DSPPacketAnalyzerV3::shared().breathingRate(),
        2
    );
    Serial.println(" RPM");

    Serial.print("Confidence     : ");
    Serial.print(
        DSPPacketAnalyzerV3::shared().confidence(),
        2
    );
    Serial.println(" %");

    Serial.println("------------------------------");
    Serial.println();
}
//--------------------------------------------------
// Human State
//--------------------------------------------------

void PacketAnalyzer::printHumanState() const
{
    Serial.println("CURRENT HUMAN STATE");
    Serial.println();

    Serial.print("State : ");

    switch (HumanStateMachine::shared().currentState())
    {
        case HumanState::Booting:
            Serial.println("Booting");
            break;

        case HumanState::Idle:
            Serial.println("Idle");
            break;

        case HumanState::PersonDetected:
            Serial.println("PersonDetected");
            break;

        case HumanState::Still:
            Serial.println("Still");
            break;

        case HumanState::Monitoring:
            Serial.println("Monitoring");
            break;

        case HumanState::Walking:
            Serial.println("Walking");
            break;

        case HumanState::Running:
            Serial.println("Running");
            break;

        case HumanState::GestureDetected:
            Serial.println("GestureDetected");
            break;

        case HumanState::FallDetected:
            Serial.println("FallDetected");
            break;

        case HumanState::Alert:
            Serial.println("Alert");
            break;

        default:
            Serial.println("Unknown");
            break;
    }

    Serial.println();

    Serial.print("Confidence : ");
    Serial.print(
        DSPPacketAnalyzerV3::shared().confidence(),
        2
    );
    Serial.println(" %");

    Serial.print("Heart BPM  : ");
    Serial.println(
        DSPPacketAnalyzerV3::shared().heartRate(),
        2
    );

    Serial.print("Breathing  : ");
    Serial.println(
        DSPPacketAnalyzerV3::shared().breathingRate(),
        2
    );

    Serial.print("Detected   : ");
    Serial.println(
        DSPPacketAnalyzerV3::shared().detected()
            ? "YES"
            : "NO"
    );

    Serial.println();
    Serial.println("========================================");
}