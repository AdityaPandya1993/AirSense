//
//  RoomEvent.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation


enum RoomEvent: Equatable {

    case personEntered
    case personLeft
    case roomStateChanged(RoomState)
    case emergency(EmergencyState)
    case vitalUpdated

}
