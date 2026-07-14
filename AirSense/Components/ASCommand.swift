//
//  ASCommand.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

import Foundation

enum ASCommand: String
{
    case hello = "HELLO"

    case ping = "PING"

    case status = "STATUS"

    case startMonitoring = "START_MONITORING"

    case stopMonitoring = "STOP_MONITORING"

    case startCSI = "START_CSI"

    case stopCSI = "STOP_CSI"

    case calibrate = "CALIBRATE"

    case reboot = "REBOOT"
}
