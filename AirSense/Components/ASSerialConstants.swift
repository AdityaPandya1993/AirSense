//
//  ASSerialConstants.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//

import Foundation

enum ASSerialConstants
{
    // MARK: - USB

    static let vendorID: Int = 0x303A      // Espressif
    static let baudRate: Int = 115200

    // MARK: - Device

    static let deviceName = "AirSense ESP32-S3"

    // MARK: - Timing

    static let heartbeatTimeout: TimeInterval = 3.0

    // MARK: - JSON

    static let heartbeatType = "heartbeat"
}
