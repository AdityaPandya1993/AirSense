//
//  SignalProcessor.h
//  AirSense Firmware
//

#ifndef SIGNAL_PROCESSOR_H
#define SIGNAL_PROCESSOR_H

#include "CSIFrame.h"

class SignalProcessor
{
public:

    static SignalProcessor& shared();

    void process(const CSIFrame& frame);

    float filteredSubcarrier(int index) const;

    float normalizedSubcarrier(int index) const;

    float lowPassSubcarrier(int index) const;

    float breathingSubcarrier(int index) const;

    float heartSubcarrier(int index) const;

private:

    SignalProcessor();

    float _filtered[64];

    float _mean[64];

    float _normalized[64];

    float _lowPass[64];

    float _breathing[64];

    float _heart[64];
};

#endif