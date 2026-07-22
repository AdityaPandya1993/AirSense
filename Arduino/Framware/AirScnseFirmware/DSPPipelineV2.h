//
//  DSPPipelineV2.h
//  AirSense Firmware
//

#ifndef DSP_PIPELINE_V2_H
#define DSP_PIPELINE_V2_H

#include <Arduino.h>

class DSPPipelineV2
{
public:

    //--------------------------------------------------
    // Singleton
    //--------------------------------------------------

    static DSPPipelineV2& shared();

    //--------------------------------------------------
    // Process One Frame
    //--------------------------------------------------

    void process();

    //--------------------------------------------------
    // Reset
    //--------------------------------------------------

    void reset();

private:

    DSPPipelineV2();

    //--------------------------------------------------
    // Pipeline Stages
    //--------------------------------------------------

    void preprocess();

    void executeFFT();

    void analyzeFrequency();

    void analyzeVitals();

    void updateConfidence();

    void updateHumanState();
};

#endif