//
//  PacketAnalyzer.cpp
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#include "PacketAnalyzer.h"

#include "IQDecoder.h"
#include "CSIConverter.h"

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
    // Convert IQ -> CSI
    //--------------------------------------------------

    CSIConverter::shared().convert(
        IQDecoder::shared().samples(),
        IQDecoder::shared().sampleCount()
    );

    //--------------------------------------------------
    // Print Packet
    //--------------------------------------------------

    printHeader();

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
    // IQ Values
    //--------------------------------------------------

    printIQPairs(
        frame,
        12,
        16
    );

    //--------------------------------------------------
    // CSI Values
    //--------------------------------------------------

    printCSISamples(
        CSIConverter::shared().samples(),
        CSIConverter::shared().sampleCount()
    );
}

void PacketAnalyzer::printHeader() const
{
    Serial.println();

    Serial.println("========================================");
    Serial.println("        AirSense Packet Analyzer");
    Serial.println("========================================");
}

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
        Serial.print("\t");

        Serial.print(iValue);
        Serial.print("\t");

        Serial.println(qValue);
    }

    Serial.println();
    Serial.println("----------------------------------------");
}

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

    Serial.println("========================================");
}