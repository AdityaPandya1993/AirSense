//
//  SignalWindow.cpp
//  AirSense Firmware
//

#include "SignalWindow.h"

SignalWindow& SignalWindow::shared()
{
    static SignalWindow window;

    return window;
}

SignalWindow::SignalWindow()
{
    _count = 0;
}

void SignalWindow::addFrame(
    const CSIFrame& frame
)
{
    if (_count < WindowSize)
    {
        _frames[_count++] = frame;
    }
    else
    {
        for (int i = 1; i < WindowSize; i++)
        {
            _frames[i - 1] = _frames[i];
        }

        _frames[WindowSize - 1] = frame;
    }
}

bool SignalWindow::isReady() const
{
    return _count >= WindowSize;
}

const CSIFrame&
SignalWindow::frame(
    int index
) const
{
    return _frames[index];
}