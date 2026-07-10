//
//  ScenarioPlayer.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//


import Foundation

final class ScenarioPlayer {

    // MARK: - Properties

    private let scenario: Scenario

    private var currentSecond = 0

    // MARK: - Init

    init(scenario: Scenario) {
        self.scenario = scenario
    }

    // MARK: - Next Event

    func nextEvent() -> ScenarioEvent? {

        currentSecond += 1

        return scenario.events.first {
            $0.second == currentSecond
        }

    }

    // MARK: - Reset

    func reset() {

        currentSecond = 0

    }

}
