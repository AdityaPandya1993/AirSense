//
//  FakeDataService.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class FakeDataService: DashboardDataProvider {

    func dashboardData() -> DashboardModel {

        let heartRate = Int.random(in: 30...85)

        let motions = [
            "Standing",
            "Walking",
            "Hand Wave"
        ]

        let signals = [
            "🟢 Excellent",
            "🟡 Good",
            "Weak"
        ]

        return DashboardModel(
            personCount: Int.random(in: 1...2),
            roomStatus: "Occupied",
            heartRate: heartRate,
            breathing: "Normal",
            motion: motions.randomElement()!,
            signal: signals.randomElement()!,
            updateTime: "Just Now",
            deviceStatus: "🟢 Connected • ESP32-S3",
            datasetCount: Int.random(in: 0...50),
            waitingMessage: "🟡 Waiting for Gesture..."
        )
    }
}
