//
//  DebugConsole.cpp
//  AirSense Firmware
//
//  Version : 2.0
//

#include "DebugConsole.h"

#include <Arduino.h>

#include "SubcarrierSelector.h"

#include "EnergyAnalyzer.h"
#include "VarianceAnalyzer.h"
#include "QualityAnalyzer.h"
#include "MotionEnergyDetector.h"

#include "HeartEngine.h"
#include "BreathingEngine.h"
#include "ConfidenceEngine.h"
#include "PeakDetector.h"
#include "CSIFrameBuffer.h"

DebugConsole&
DebugConsole::shared()
{
    static DebugConsole console;
    return console;
}

DebugConsole::DebugConsole()
{

}

void DebugConsole::printDSP()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("        AirSense DSP Debug");
    Serial.println("========================================");

    //--------------------------------------
// Buffer Status
//--------------------------------------

//--------------------------------------
// Buffer Status
//--------------------------------------

Serial.print("Buffer Ready       : ");

Serial.println(
    CSIFrameBuffer::shared().isFull()
        ? "YES"
        : "NO"
);

Serial.print("Frame Count        : ");

Serial.println(
    CSIFrameBuffer::shared().count()
);
    //--------------------------------------
    // Best Subcarrier
    //--------------------------------------

    Serial.print("Best Subcarrier     : ");
    Serial.println(
        SubcarrierSelector::shared()
            .bestSubcarrier()
    );

    //--------------------------------------
    // Energy
    //--------------------------------------

    Serial.print("Signal Energy       : ");
    Serial.println(
        EnergyAnalyzer::shared()
            .currentEnergy(),
        4
    );

    //--------------------------------------
    // Variance
    //--------------------------------------

    Serial.print("Signal Variance     : ");
    Serial.println(
        VarianceAnalyzer::shared()
            .currentVariance(),
        4
    );

    //--------------------------------------
    // Quality
    //--------------------------------------

    Serial.print("Quality Score       : ");
    Serial.println(
        QualityAnalyzer::shared()
            .currentQuality(),
        4
    );

    //--------------------------------------
    // Motion
    //--------------------------------------

    Serial.print("Motion Energy       : ");
    Serial.println(
        MotionEnergyDetector::shared()
            .motionEnergy(),
        4
    );

    Serial.print("Motion Detected     : ");
    Serial.println(
        MotionEnergyDetector::shared()
            .isMoving()
            ? "YES"
            : "NO"
    );

    //--------------------------------------
// FFT Peak
//--------------------------------------

Serial.print("Peak Value          : ");
Serial.println(
    PeakDetector::shared()
        .peakValue(),
    4
);

    //--------------------------------------
    // Heart
    //--------------------------------------

    Serial.print("Heart Frequency     : ");
    Serial.print(
        HeartEngine::shared()
            .currentFrequency(),
        2
    );
    Serial.println(" Hz");

    Serial.print("Heart Rate          : ");
    Serial.print(
        HeartEngine::shared()
            .currentHeartRate()
    );
    Serial.println(" BPM");

    //--------------------------------------
    // Breathing
    //--------------------------------------

    Serial.print("Breathing Frequency : ");
    Serial.print(
        BreathingEngine::shared()
            .currentFrequency(),
        2
    );
    Serial.println(" Hz");

    Serial.print("Breathing Rate      : ");
    Serial.print(
        BreathingEngine::shared()
            .currentBreathingRate()
    );
    Serial.println(" BPM");

    //--------------------------------------
    // Confidence
    //--------------------------------------

    Serial.print("Confidence          : ");
    Serial.print(
        ConfidenceEngine::shared()
            .confidence(),
        1
    );
    Serial.println(" %");

    Serial.println("========================================");
    Serial.println();
}

//--------------------------------------------------
// Debug Output
//--------------------------------------------------
