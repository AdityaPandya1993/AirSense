//
//  CSIGenerator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

final class CSIGenerator {

    private let waveGenerator = WaveGenerator()

    func generate(signal: HumanSignal) -> CSIFrame {

        var packets: [CSIPacket] = []

        // Base Signal & Amplitude
        var base: Double
        var amplitude: Double

        switch signal.motion {

        case .standing:
            base = -42.0
            amplitude = 0.30

        case .walking:
            base = -38.0
            amplitude = 1.20

        case .waving:
            base = -32.0
            amplitude = 2.50

        case .sitting:
            base = -41.0
            amplitude = 0.40

        case .sleeping:
            base = -44.0
            amplitude = 0.15

        case .leaving:
            base = -46.0
            amplitude = 0.80
        }

        // Heart Rate Effect
        let heartEffect = Double(signal.heartRate - 70) * 0.02

        // Breathing Effect
        let breathingEffect = (signal.breathingRate - 14.0) * 0.05

        base += heartEffect
        base += breathingEffect

        // Generate 10 CSI Packets
        for _ in 0..<10 {

            let subcarriers = waveGenerator.generateWave(
                base: base,
                amplitude: amplitude
            )

            let packet = CSIPacket(
                timestamp: Date(),
                subcarriers: subcarriers
            )

            packets.append(packet)
        }

        return CSIFrame(packets: packets)
    }
}
