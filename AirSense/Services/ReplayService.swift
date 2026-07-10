//
//  ReplayService.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//
import Foundation

final class ReplayService: DashboardDataProvider {

    func dashboardData() -> DashboardModel {

        // હાલ Dummy Data
        return DashboardModel(
            personCount: 0,
            roomStatus: "Replay Mode",
            heartRate: 0,
            breathing: "Loading...",
            motion: "Replay",
            signal: "Dataset",
            updateTime: "Replay",
            deviceStatus: "Replay Mode",
            datasetCount: 250,
            waitingMessage: "Reading Dataset..."
        )

    }

}
