//
//  CSIBuffer.cpp
//  AirSense Firmware
//

#include "CSIBuffer.h"

CSIBuffer& CSIBuffer::shared()
{
    static CSIBuffer buffer;
    return buffer;
}

CSIBuffer::CSIBuffer()
{
    _count = 0;
}

void CSIBuffer::addFrame(const CSIFrame& frame)
{
    if (_count < MAX_FRAMES)
    {
        _frames[_count++] = frame;
        return;
    }

    for (int i = 1; i < MAX_FRAMES; i++)
    {
        _frames[i - 1] = _frames[i];
    }

    _frames[MAX_FRAMES - 1] = frame;
}

int CSIBuffer::count() const
{
    return _count;
}

const CSIFrame& CSIBuffer::frameAt(int index) const
{
    return _frames[index];
}

void CSIBuffer::clear()
{
    _count = 0;
}