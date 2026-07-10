//
//  SimulationWindow.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class SimulationWindow: SimulationObject {

    var isOpen: Bool

    init(
        name: String,
        x: Double,
        y: Double,
        isOpen: Bool
    ) {

        self.isOpen = isOpen

        super.init(
            name: name,
            x: x,
            y: y
        )

    }

}
