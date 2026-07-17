//
//  CSIFrameBuffer.h
//  AirSense Firmware
//

#ifndef CSI_FRAME_BUFFER_H
#define CSI_FRAME_BUFFER_H

#include "CSIFrame.h"
#include "DSPConstants.h"

class CSIFrameBuffer
{
public:

    static CSIFrameBuffer& shared();

    void push(
        const CSIFrame& frame
    );

    bool isFull() const;

    int count() const;

    const CSIFrame& frame(
        int index
    ) const;

    void clear();

private:

    CSIFrameBuffer();

private:

    static constexpr int BufferSize = DSP::FFTSize;

    CSIFrame _frames[BufferSize];

    int _count;

    int _head;
};

#endif