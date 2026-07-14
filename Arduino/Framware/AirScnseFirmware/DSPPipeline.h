//
//  DSPPipeline.h
//  AirSense Firmware
//

#ifndef DSP_PIPELINE_H
#define DSP_PIPELINE_H

#include "CSIFrame.h"

class DSPPipeline
{
public:

    static DSPPipeline& shared();

    void process(
        const CSIFrame& frame
    );

private:

    DSPPipeline();
};

#endif