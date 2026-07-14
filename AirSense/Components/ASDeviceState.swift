//
//  ASDeviceState.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

import Foundation

enum ASDeviceState: String
{
    case booting = "BOOTING"

    case ready = "READY"

    case calibrating = "CALIBRATING"

    case monitoring = "MONITORING"

    case alert = "ALERT"

    case disconnected = "DISCONNECTED"
}
