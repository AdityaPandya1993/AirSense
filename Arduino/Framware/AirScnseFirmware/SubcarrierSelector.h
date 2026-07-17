//
//  SubcarrierSelector.h
//  AirSense Firmware
//

#ifndef SUBCARRIER_SELECTOR_H
#define SUBCARRIER_SELECTOR_H

class SubcarrierSelector
{
public:

    static SubcarrierSelector& shared();

    void analyze();

    int bestSubcarrier() const;

    float quality() const;

private:

    SubcarrierSelector();

private:

    int _bestSubcarrier;

    float _quality;
};

#endif