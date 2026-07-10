//
//  ESP32Services.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class ESP32Service: DashboardDataProvider {

    func dashboardData() -> DashboardModel {

        return DashboardModel(
            personCount: 0,
            roomStatus: "Waiting",
            heartRate: 0,
            breathing: "--",
            motion: "--",
            signal: "Disconnected",
            updateTime: "--",
            deviceStatus: "Searching ESP32...",
            datasetCount: 0,
            waitingMessage: "Waiting Device..."
        )

    }
}
