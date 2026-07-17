//
//  QualityAnalyzer.cpp
//  AirSense Firmware
//
//  Version : 2.0
//

#include "QualityAnalyzer.h"

QualityAnalyzer&
QualityAnalyzer::shared()
{
    static QualityAnalyzer analyzer;
    return analyzer;
}

QualityAnalyzer::QualityAnalyzer()
{
    _currentQuality = 0.0f;
}

void QualityAnalyzer::update(
    float energy,
    float variance
)
{
    //--------------------------------------------------
    // Prevent Divide By Zero
    //--------------------------------------------------

    const float epsilon = 0.0001f;

    _currentQuality =
        energy / (variance + epsilon);
}

float QualityAnalyzer::currentQuality() const
{
    return _currentQuality;
}