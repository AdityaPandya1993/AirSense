//
//  SimulationEngineDelegate.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

protocol SimulationEngineDelegate: AnyObject {

    func simulationDidUpdate(
        _ human: HumanEntity,
        csiFrame: CSIFrame
    )

}
