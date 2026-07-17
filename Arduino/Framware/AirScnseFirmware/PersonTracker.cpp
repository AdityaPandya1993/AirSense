//
//  PersonTracker.cpp
//  AirSense Firmware
//
//  Module-04
//

#include "PersonTracker.h"

#include <Arduino.h>

PersonTracker&
PersonTracker::shared()
{
    static PersonTracker tracker;
    return tracker;
}

PersonTracker::PersonTracker()
{
    _track.id = 1;
    _track.active = false;
    _track.lastSeen = 0;
}

void PersonTracker::update(
    const PersonObservation& observation
)
{
    //----------------------------------
    // Store Latest Observation
    //----------------------------------

    _track.observation = observation;

    //----------------------------------
    // Detection State
    //----------------------------------

    _track.active = observation.detected;

    //----------------------------------
    // Last Seen
    //----------------------------------

    if (observation.detected)
    {
        _track.lastSeen = millis();
    }
}

const PersonTrack&
PersonTracker::currentTrack() const
{
    return _track;
}