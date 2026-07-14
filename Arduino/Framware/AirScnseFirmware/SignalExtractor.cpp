//
// SignalExtractor.cpp
//

#include "SignalExtractor.h"

SignalExtractor&
SignalExtractor::shared()
{
    static SignalExtractor extractor;

    return extractor;
}

SignalExtractor::SignalExtractor()
{
    for (int i = 0; i < SampleCount; i++)
    {
        _samples[i] = 0.0f;
    }
}

void SignalExtractor::extract()
{
    for (int i = 0; i < SampleCount; i++)
    {
        _samples[i] =
            SignalWindow::shared()
                .frame(i)
                .subcarriers[SelectedSubcarrier];
    }
}

float SignalExtractor::sample(
    int index
) const
{
    if (index < 0 || index >= SampleCount)
    {
        return 0.0f;
    }

    return _samples[index];
}