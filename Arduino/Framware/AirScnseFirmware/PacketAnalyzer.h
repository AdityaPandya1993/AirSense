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
#include "CenteredSample.h"
#include "FilteredSample.h"

class PacketAnalyzer
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static PacketAnalyzer& shared();

    //--------------------------------------------------
    // Initialize
    //--------------------------------------------------

    void begin();

    //--------------------------------------------------
    // Analyze Packet
    //--------------------------------------------------

    void analyze(
        const RawCSIFrame& frame
    );

private:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    PacketAnalyzer();

    //--------------------------------------------------
    // Packet Info
    //--------------------------------------------------

    void printHeader() const;

    void printSummary(
        const RawCSIFrame& frame
    ) const;

    //--------------------------------------------------
    // Raw Packet
    //--------------------------------------------------

    void printSignedSamples(
        const RawCSIFrame& frame,
        uint16_t startOffset,
        uint16_t sampleCount
    ) const;

    //--------------------------------------------------
    // IQ
    //--------------------------------------------------

    void printIQPairs(
        const RawCSIFrame& frame,
        uint16_t startOffset,
        uint16_t pairCount
    ) const;

    //--------------------------------------------------
    // CSI
    //--------------------------------------------------

    void printCSISamples(
        const CSISample* samples,
        uint16_t count
    ) const;

    //--------------------------------------------------
    // DC Removal
    //--------------------------------------------------

    void printCenteredSamples(
        const CSISample* original,
        const CenteredSample* centered,
        uint16_t count,
        float mean
    ) const;

    //--------------------------------------------------
    // Low Pass Filter
    //--------------------------------------------------

    void printFilteredSamples(
        const CenteredSample* original,
        const FilteredSample* filtered,
        uint16_t count
    ) const;

    //--------------------------------------------------
    // Motion Energy
    //--------------------------------------------------

    void printMotionEnergyFilter(
        float rawEnergy,
        float filteredEnergy
    ) const;

    //--------------------------------------------------
    // Human State
    //--------------------------------------------------

    void printHumanState() const;
};

#endif