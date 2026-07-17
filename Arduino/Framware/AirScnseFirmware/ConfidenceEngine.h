//
//  ConfidenceEngine.h
//  AirSense Firmware
//
//  Version : 1.0
//

#ifndef CONFIDENCE_ENGINE_H
#define CONFIDENCE_ENGINE_H

class ConfidenceEngine
{
public:

    static ConfidenceEngine& shared();

    void update(
        float quality,
        float motion,
        float peak,
        float variance
    );

    float confidence() const;

private:

    ConfidenceEngine();

private:

    float _confidence;
};

#endif