//
//  WiFiManager.h
//  AirSense Firmware
//

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

class WiFiManager
{
public:

    static WiFiManager& shared();

    void begin();

    bool isReady() const;

private:

    WiFiManager();

private:

    bool _ready;
};

#endif