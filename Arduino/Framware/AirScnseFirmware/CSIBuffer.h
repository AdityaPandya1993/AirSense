//
//  CSIBuffer.h
//  AirSense Firmware
//

#ifndef CSI_BUFFER_H
#define CSI_BUFFER_H

#include "CSIFrame.h"

class CSIBuffer
{
public:

    static CSIBuffer& shared();

    void addFrame(const CSIFrame& frame);

    int count() const;

    const CSIFrame& frameAt(int index) const;

    void clear();

private:

    CSIBuffer();

    static const int MAX_FRAMES = 300;

    CSIFrame _frames[MAX_FRAMES];

    int _count;
};

#endif