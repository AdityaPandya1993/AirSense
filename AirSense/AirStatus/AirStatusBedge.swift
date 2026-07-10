//
//  AirStatusBedge.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

enum AirStatus {

    case connected
    case disconnected
    case waiting
    case processing
    case learning

    var color: NSColor {

        switch self {

        case .connected:
            return .systemGreen

        case .disconnected:
            return .systemRed

        case .waiting:
            return .systemGray

        case .processing:
            return .systemOrange

        case .learning:
            return .systemBlue
        }
    }

    var title: String {

        switch self {

        case .connected:
            return "Connected"

        case .disconnected:
            return "Disconnected"

        case .waiting:
            return "Waiting"

        case .processing:
            return "Processing"

        case .learning:
            return "Learning"
        }
    }

}
