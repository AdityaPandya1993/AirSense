//
//  PersonTrack.h
//  AirSense Firmware
//
//  Module-04
//

#ifndef PERSON_TRACK_H
#define PERSON_TRACK_H

#include "PersonObservation.h"

struct PersonTrack
{
    //----------------------------------
    // Tracking
    //----------------------------------

    int id;

    bool active;

    unsigned long lastSeen;

    //----------------------------------
    // Latest Observation
    //----------------------------------

    PersonObservation observation;

    //----------------------------------
    // Constructor
    //----------------------------------

    PersonTrack()
    {
        id = -1;
        active = false;
        lastSeen = 0;
    }
};

#endif