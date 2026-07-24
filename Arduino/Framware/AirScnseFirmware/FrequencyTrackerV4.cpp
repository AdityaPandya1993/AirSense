#include "FrequencyTrackerV4.h"

FrequencyTrackerV4&
FrequencyTrackerV4::shared()
{
    static FrequencyTrackerV4 instance;
    return instance;
}

FrequencyTrackerV4::FrequencyTrackerV4()
{
    _index = 0;
    _frequency = 0;

    for(int i=0;i<5;i++)
        _history[i]=0;
}

void FrequencyTrackerV4::begin()
{
}

void FrequencyTrackerV4::update(
    float frequency
)
{
    _history[_index]=frequency;

    _index++;

    if(_index>=5)
        _index=0;

    float sum=0;

    for(int i=0;i<5;i++)
        sum+=_history[i];

    _frequency=sum/5.0f;
}

float FrequencyTrackerV4::value() const
{
    return _frequency;
}