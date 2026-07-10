//
//  DashboardViewModel.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class DashboardViewModel {

    private let fakeService = FakeDataService()
    private let replayService = ReplayService()
    private let esp32Service = ESP32Service()

    private(set) var dashboard: DashboardModel?

    func loadData() {

        switch AppConfiguration.shared.mode {

        case .simulation:
            dashboard = fakeService.dashboardData()

        case .replay:
            dashboard = replayService.dashboardData()

        case .live:
            dashboard = esp32Service.dashboardData()
        }

    }

}
