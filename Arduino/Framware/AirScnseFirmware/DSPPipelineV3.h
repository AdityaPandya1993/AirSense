// //
// //  DSPPipelineV3.h
// //  AirSense Firmware
// //

// #ifndef DSP_PIPELINE_V3_H
// #define DSP_PIPELINE_V3_H

// #include <Arduino.h>

// class DSPPipelineV3
// {
// public:

//     //--------------------------------------------------
//     // Singleton
//     //--------------------------------------------------

//     static DSPPipelineV3& shared();

//     //--------------------------------------------------
//     // Initialize
//     //--------------------------------------------------

//     bool begin();

//     //--------------------------------------------------
//     // Process Complete DSP
//     //--------------------------------------------------

//     void process(
//         const float* samples,
//         uint16_t count,
//         float sampleRate
//     );

//     //--------------------------------------------------
//     // Results
//     //--------------------------------------------------

//     float heartRate() const;

//     float breathingRate() const;

//     float confidence() const;

//     bool humanDetected() const;

//     //--------------------------------------------------
//     // Reset
//     //--------------------------------------------------

//     void reset();

// private:

//     DSPPipelineV3();

// private:

//     bool _ready;
// };

// #endif