//
//  ASSerialConstants.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//

import Foundation

enum ASSerialConstants
{
    // MARK: - Serial Configuration

    static let baudRate: Int = 115200

    static let dataBits: Int = 8

    static let stopBits: Int = 1

    static let parityEnabled: Bool = false

    static let hardwareFlowControl: Bool = false

    // MARK: - Buffer

    static let readBufferSize: Int = 4096

    static let writeBufferSize: Int = 4096

    // MARK: - Timeouts

    static let readTimeout: TimeInterval = 1.0

    static let writeTimeout: TimeInterval = 1.0

    // MARK: - Device Detection

    static let supportedDevicePrefixes =
    [
        "usbmodem",
        "usbserial",
        "tty.usbmodem",
        "tty.usbserial"
    ]
}
