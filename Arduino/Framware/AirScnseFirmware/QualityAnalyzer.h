//
//  QualityAnalyzer.h
//  AirSense Firmware
//
//  Version : 2.0
//

#ifndef QUALITY_ANALYZER_H
#define QUALITY_ANALYZER_H

class QualityAnalyzer
{
public:

    static QualityAnalyzer& shared();

    void update(
        float energy,
        float variance
    );

    float currentQuality() const;

private:

    QualityAnalyzer();

private:

    float _currentQuality;
};

#endif