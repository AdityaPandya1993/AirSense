//
//  CSIManager.h
//  AirSense Firmware
//

#ifndef CSI_MANAGER_H
#define CSI_MANAGER_H

#include "CSIFrame.h"

class CSIManager
{
public:

    static CSIManager& shared();

    void begin();

    void update();

    CSIFrame currentFrame() const;

private:

    CSIManager();

    CSIFrame _frame;
};

#endif