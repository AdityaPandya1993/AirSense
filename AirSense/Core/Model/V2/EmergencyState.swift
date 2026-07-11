//
//  EmergencyState.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation


enum EmergencyState: String, Codable {

    case none
    case fallDetected
    case abnormalHeartRate
    case abnormalBreathing
    case noMovement
    case sos

}
