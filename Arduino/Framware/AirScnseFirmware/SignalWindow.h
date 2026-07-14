//
//  SignalWindow.h
//  AirSense Firmware
//

#ifndef SIGNAL_WINDOW_H
#define SIGNAL_WINDOW_H

#include "CSIFrame.h"

class SignalWindow
{
public:

    static SignalWindow& shared();

    void addFrame(const CSIFrame& frame);

    bool isReady() const;

    const CSIFrame& frame(int index) const;

    static const int WindowSize = 128;

private:

    SignalWindow();

    CSIFrame _frames[WindowSize];

    int _count;
};

#endif