//
//  SimulationPerson.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation


final class SimulationPerson: SimulationObject {

    var heartRate: Int

    var breathingRate: Double

    init(
        name: String,
        x: Double,
        y: Double,
        heartRate: Int,
        breathingRate: Double
    ) {

        self.heartRate = heartRate
        self.breathingRate = breathingRate

        super.init(
            name: name,
            x: x,
            y: y
        )

    }

}
