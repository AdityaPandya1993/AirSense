//
//  DefaultScenario.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

enum DefaultScenario {

    static let morning = Scenario(

        name: "Morning",

        events: [

            ScenarioEvent(
                second: 1,
                motion: MotionState.standing,
                heartRate: 72,
                breathingRate: 14,
                position: Coordinate(x: 2, y: 2)
            ),

            ScenarioEvent(
                second: 6,
                motion: MotionState.walking,
                heartRate: 78,
                breathingRate: 16,
                position: Coordinate(x: 3, y: 2)
            ),

            ScenarioEvent(
                second: 11,
                motion: MotionState.waving,
                heartRate: 82,
                breathingRate: 18,
                position: Coordinate(x: 4, y: 2)
            )

        ]

    )

}
