//
//  DashboardModel.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

struct DashboardModel {
    
    var heartStatus: HealthStatus {

        switch heartRate {

        case 70...90:
            return .normal

        case 50..<80, 91...110:
            return .warning

        default:
            return .critical
        }
    }

    let personCount: Int
    let roomStatus: String
    let heartRate: Int
    let breathing: String
    let motion: String
    let signal: String
    let updateTime: String

    let deviceStatus: String
    let datasetCount: Int
    let waitingMessage: String

}

enum HealthStatus {

    case normal
    case warning
    case critical

}
