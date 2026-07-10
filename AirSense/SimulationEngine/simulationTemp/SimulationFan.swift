//
//  SimulationFan.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class SimulationFan: SimulationObject {

    var speed: Int
    var isRunning: Bool

    init(
        name: String,
        x: Double,
        y: Double,
        speed: Int,
        isRunning: Bool
    ) {

        self.speed = speed
        self.isRunning = isRunning

        super.init(
            name: name,
            x: x,
            y: y
        )

    }

}
