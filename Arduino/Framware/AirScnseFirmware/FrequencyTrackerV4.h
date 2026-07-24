#ifndef FREQUENCY_TRACKER_V4_H
#define FREQUENCY_TRACKER_V4_H

#include <Arduino.h>

class FrequencyTrackerV4
{
public:

    static FrequencyTrackerV4& shared();

    void begin();

    void update(float frequency);

    float value() const;

private:

    FrequencyTrackerV4();

private:

    float _history[5];

    uint8_t _index;

    float _frequency;
};

#endif