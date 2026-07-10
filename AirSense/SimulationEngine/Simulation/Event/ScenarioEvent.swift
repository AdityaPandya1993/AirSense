//
//  ScenarioEvent.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

struct ScenarioEvent {

    let second: Int

    let motion: Int
    
    enum RoomEvent {

        case personEntered

        case personLeft

        case roomStateChanged(RoomState)

        case emergency(EmergencyState)

        case vitalUpdated

    }

    let heartRate: Int

    let breathingRate: Double

    let position: Coordinate

}
