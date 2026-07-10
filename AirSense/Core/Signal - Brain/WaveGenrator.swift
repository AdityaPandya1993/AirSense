//
//  WaveGenrator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

final class WaveGenerator {
    
    
    
    

    func generateWave(
        base: Double,
        amplitude: Double,
        count: Int = 64,
        noise: Double = 0.25
    ) -> [Double] {
        
        
        var previousWave: [Double] = []
        var values: [Double] = []
        
        if previousWave.isEmpty {

            previousWave = Array(
                repeating: base,
                count: count
            )

        }

        for index in 0..<count {

            let angle = Double(index) * 0.25

            let target =
                base +
                sin(angle) * amplitude

            let smooth =
                previousWave[index] +
                (target - previousWave[index]) * 0.20

            let randomNoise =
                Double.random(in: -noise...noise)

            values.append(
                smooth + randomNoise
            )

        }
        
        previousWave = values

        return values

    }

}
