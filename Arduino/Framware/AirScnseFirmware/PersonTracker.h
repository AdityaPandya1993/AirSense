//
//  PersonTracker.h
//  AirSense Firmware
//
//  Module-04
//

#ifndef PERSON_TRACKER_H
#define PERSON_TRACKER_H

#include "PersonTrack.h"
#include "PersonObservation.h"

class PersonTracker
{
public:

    static PersonTracker& shared();

    void update(
        const PersonObservation& observation
    );

    const PersonTrack& currentTrack() const;

private:

    PersonTracker();

private:

    PersonTrack _track;
};

#endif