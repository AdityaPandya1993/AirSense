//
//  PacketAnalyzer.h
//  AirSense Firmware
//
//  Created by Aditya Pandya
//

#ifndef PACKET_ANALYZER_H
#define PACKET_ANALYZER_H

#include <Arduino.h>

#include "RawCSIFrame.h"
#include "CSISample.h"

class PacketAnalyzer
{
public:

    static PacketAnalyzer& shared();

    void begin();

    void analyze(
        const RawCSIFrame& frame
    );

private:

    PacketAnalyzer();

private:

    void printHeader() const;

    void printSummary(
        const RawCSIFrame& frame
    ) const;

    void printSignedSamples(
        const RawCSIFrame& frame,
        uint16_t startOffset,
        uint16_t sampleCount
    ) const;

    void printIQPairs(
        const RawCSIFrame& frame,
        uint16_t startOffset,
        uint16_t pairCount
    ) const;

    void printCSISamples(
        const CSISample* samples,
        uint16_t count
    ) const;
};

#endif