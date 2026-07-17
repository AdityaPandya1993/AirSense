//
//  VarianceAnalyzer.h
//  AirSense Firmware
//
//  Version : 2.0
//

#ifndef VARIANCE_ANALYZER_H
#define VARIANCE_ANALYZER_H

class VarianceAnalyzer
{
public:

    static VarianceAnalyzer& shared();

    void update(
        const float* samples,
        int count
    );

    float currentVariance() const;

private:

    VarianceAnalyzer();

private:

    float _currentVariance;
};

#endif