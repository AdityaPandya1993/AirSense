#ifndef CSI_RECEIVER_H
#define CSI_RECEIVER_H

#include "CSIFrame.h"

class CSIReceiver
{
public:

    static CSIReceiver& shared();

    bool begin();

    bool isEnabled() const;

    void onCSIFrame(const CSIFrame& frame);

private:

    CSIReceiver();

private:

    bool _enabled;
};

#endif