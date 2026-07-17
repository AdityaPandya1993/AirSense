//
//  CSIDriver.h
//  AirSense Firmware
//

#ifndef CSI_DRIVER_H
#define CSI_DRIVER_H

#include <Arduino.h>

extern "C"
{
    #include "esp_wifi.h"
}

class CSIDriver
{
public:

    static CSIDriver& shared();

    bool begin();

    bool started() const;

private:

    CSIDriver();

    bool enableCSI();

    bool registerCallback();

    static void wifiCsiCallback(
        void* ctx,
        wifi_csi_info_t* info
    );

private:

    bool _started;
};

#endif