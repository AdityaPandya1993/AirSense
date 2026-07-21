//
//  PacketAnalyzer.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "PacketAnalyzer.h"

#include "IQDecoder.h"
#include "CSIConverter.h"
#include "DCRemoval.h"
#include "LowPassFilter.h"

PacketAnalyzer&
PacketAnalyzer::shared()
{
    static PacketAnalyzer analyzer;

    return analyzer;
}

PacketAnalyzer::PacketAnalyzer()
{
}

void PacketAnalyzer::begin()
{
    Serial.println();

    Serial.println("========================================");
    Serial.println("     AirSense Packet Analyzer Ready");
    Serial.println("========================================");
}

void PacketAnalyzer::analyze(
    const RawCSIFrame& frame
)
{
    //--------------------------------------------------
    // Decode IQ
    //--------------------------------------------------

    IQDecoder::shared().decode(frame);

    //--------------------------------------------------
    // IQ -> CSI
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
    // Print Header
    //--------------------------------------------------

    printHeader();

    //--------------------------------------------------
    // Packet Summary
    //--------------------------------------------------

    printSummary(frame);
        //--------------------------------------------------
    // Raw Signed Values
    //--------------------------------------------------

    printSignedSamples(
        frame,
        12,
        32
    );

    //--------------------------------------------------
    // IQ Samples
    //--------------------------------------------------

    printIQPairs(
        frame,
        12,
        16
    );

    //--------------------------------------------------
    // CSI Samples
    //--------------------------------------------------

    printCSISamples(
        CSIConverter::shared().samples(),
        CSIConverter::shared().sampleCount()
    );

    //--------------------------------------------------
    // DC Removal
    //--------------------------------------------------

    printCenteredSamples(
        CSIConverter::shared().samples(),
        DCRemoval::shared().samples(),
        DCRemoval::shared().sampleCount(),
        DCRemoval::shared().meanAmplitude()
    );

    //--------------------------------------------------
    // Low Pass Filter
    //--------------------------------------------------

    printFilteredSamples(
        DCRemoval::shared().samples(),
        LowPassFilter::shared().samples(),
        LowPassFilter::shared().sampleCount()
    );
}

//
// MARK: - Header
//

void PacketAnalyzer::printHeader() const
{
    Serial.println();

    Serial.println("========================================");
    Serial.println("        AirSense Packet Analyzer");
    Serial.println("========================================");
}

//
// MARK: - Summary
//

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
//
// MARK: - Signed Samples
//

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

        Serial.print((int8_t)frame.data[startOffset + i]);
        Serial.print("\t");

        if ((i + 1) % 8 == 0)
        {
            Serial.println();
        }
    }

    Serial.println();
    Serial.println("----------------------------------------");
}

//
// MARK: - IQ Samples
//

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
            (int8_t)frame.data[index];

        int8_t qValue =
            (int8_t)frame.data[index + 1];

        Serial.print(i);
        Serial.print("\t");

        Serial.print(iValue);
        Serial.print("\t");

        Serial.println(qValue);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}
//
// MARK: - CSI Samples
//

void PacketAnalyzer::printCSISamples(
    const CSISample* samples,
    uint16_t count
) const
{
    Serial.println("CSI CONVERTER OUTPUT");
    Serial.println();

    Serial.println("Idx\tAmplitude\tPhase");

    uint16_t maxSamples = count;

    if (maxSamples > 16)
    {
        maxSamples = 16;
    }

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(samples[i].index);
        Serial.print("\t");

        Serial.print(samples[i].amplitude, 4);
        Serial.print("\t\t");

        Serial.println(samples[i].phase, 4);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}

//
// MARK: - DC Removal
//

void PacketAnalyzer::printCenteredSamples(
    const CSISample* original,
    const CenteredSample* centered,
    uint16_t count,
    float mean
) const
{
    Serial.println("DC REMOVAL");
    Serial.println();

    Serial.print("Mean Amplitude : ");
    Serial.println(mean, 4);

    Serial.println();
    Serial.println("Idx\tOriginal\tCentered");

    uint16_t maxSamples = count;

    if (maxSamples > 16)
    {
        maxSamples = 16;
    }

    float centeredMean = 0.0f;

    //--------------------------------------------------
    // Calculate Mean Using ALL Samples
    //--------------------------------------------------

    for (uint16_t i = 0; i < count; i++)
    {
        centeredMean += centered[i].amplitude;
    }

    centeredMean /= count;

    //--------------------------------------------------
    // Print First Samples
    //--------------------------------------------------

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(centered[i].index);
        Serial.print("\t");

        Serial.print(original[i].amplitude, 4);
        Serial.print("\t\t");

        Serial.println(centered[i].amplitude, 4);
    }

    Serial.println();

    Serial.print("Centered Mean : ");
    Serial.println(centeredMean, 6);

    Serial.println();
    Serial.println("----------------------------------------");
}

//
// MARK: - Low Pass Filter
//

void PacketAnalyzer::printFilteredSamples(
    const CenteredSample* centered,
    const FilteredSample* filtered,
    uint16_t count
) const
{
    Serial.println("LOW PASS FILTER");
    Serial.println();

    Serial.println("Idx\tCentered\tFiltered");

    uint16_t maxSamples = count;

    if (maxSamples > 16)
    {
        maxSamples = 16;
    }

    for (uint16_t i = 0; i < maxSamples; i++)
    {
        Serial.print(filtered[i].index);
        Serial.print("\t");

        Serial.print(centered[i].amplitude, 4);
        Serial.print("\t\t");

        Serial.println(filtered[i].amplitude, 4);
    }

    Serial.println();
    Serial.println("========================================");
}