//
//  PersonObservation.h
//  AirSense Firmware
//
//  Module-04
//

#ifndef PERSON_OBSERVATION_H
#define PERSON_OBSERVATION_H

struct PersonObservation
{
    //----------------------------------
    // Detection
    //----------------------------------

    bool detected;

    //----------------------------------
    // Motion
    //----------------------------------

    bool moving;

    //----------------------------------
    // Vital Signs
    //----------------------------------

    float heartRate;

    float breathingRate;

    //----------------------------------
    // Signal Quality
    //----------------------------------

    float confidence;

    float quality;

    float motionEnergy;

    //----------------------------------
    // Constructor
    //----------------------------------

    PersonObservation()
    {
        detected = false;
        moving = false;

        heartRate = 0.0f;
        breathingRate = 0.0f;

        confidence = 0.0f;
        quality = 0.0f;
        motionEnergy = 0.0f;
    }
};

#endif