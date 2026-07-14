//
//  CSIManager.cpp
//  AirSense Firmware
//

#include "CSIManager.h"
#include <math.h>

CSIManager& CSIManager::shared()
{
    static CSIManager manager;
    return manager;
}

CSIManager::CSIManager()
{
}

void CSIManager::begin()
{
}

void CSIManager::update()
{
    _frame.timestamp = millis();

    _frame.rssi = -45;

    _frame.noise = -92;

    _frame.sequence++;

    _frame.channel = 6;

    _frame.bandwidth = 20;

    for (int i = 0; i < 64; i++)
    {
        _frame.subcarriers[i] =
            sin((millis() / 200.0f) + (i * 0.15f));
    }
}

CSIFrame CSIManager::currentFrame() const
{
    return _frame;
}