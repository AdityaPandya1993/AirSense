//
// SignalExtractor.h
//

#ifndef SIGNAL_EXTRACTOR_H
#define SIGNAL_EXTRACTOR_H

#include "SignalWindow.h"

class SignalExtractor
{
public:

    static SignalExtractor& shared();

    void extract();

    float sample(int index) const;

    static const int SampleCount =
        SignalWindow::WindowSize;

private:

    SignalExtractor();

    float _samples[SampleCount];

    static const int SelectedSubcarrier = 32;
};

#endif