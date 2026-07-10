//
//  SimulationObject.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

class SimulationObject {

    let id = UUID()

    var name: String

    var x: Double

    var y: Double

    init(
        name: String,
        x: Double,
        y: Double
    ) {

        self.name = name
        self.x = x
        self.y = y

    }

}
