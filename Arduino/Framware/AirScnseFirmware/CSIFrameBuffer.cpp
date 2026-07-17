//
//  CSIFrameBuffer.cpp
//  AirSense Firmware
//

#include "CSIFrameBuffer.h"

CSIFrameBuffer&
CSIFrameBuffer::shared()
{
    static CSIFrameBuffer buffer;

    return buffer;
}

CSIFrameBuffer::CSIFrameBuffer()
{
    clear();
}

void CSIFrameBuffer::clear()
{
    _count = 0;
    _head = 0;
}

void CSIFrameBuffer::push(
    const CSIFrame& frame
)
{
    _frames[_head] = frame;

    _head++;

    if (_head >= BufferSize)
    {
        _head = 0;
    }

    if (_count < BufferSize)
    {
        _count++;
    }
}

bool CSIFrameBuffer::isFull() const
{
    return (_count == BufferSize);
}

int CSIFrameBuffer::count() const
{
    return _count;
}

const CSIFrame&
CSIFrameBuffer::frame(
    int index
) const
{
    static CSIFrame emptyFrame;

    if (index < 0 || index >= _count)
    {
        return emptyFrame;
    }

    int start = _head - _count;

    if (start < 0)
    {
        start += BufferSize;
    }

    int realIndex =
        (start + index) % BufferSize;

    return _frames[realIndex];
}