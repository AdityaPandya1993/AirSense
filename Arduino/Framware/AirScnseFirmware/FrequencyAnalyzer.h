//
//  FrequencyAnalyzer.h
//  AirSense Firmware
//

#ifndef FREQUENCY_ANALYZER_H
#define FREQUENCY_ANALYZER_H

class FrequencyAnalyzer
{
public:

    static FrequencyAnalyzer& shared();

    float peakFrequency(
        int peakIndex,
        int fftSize,
        float sampleRate
    );

    float frequencyToBPM(
        float frequency
    );

private:

    FrequencyAnalyzer();
};

#endif