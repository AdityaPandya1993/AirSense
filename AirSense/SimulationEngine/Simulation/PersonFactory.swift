//
//  PersonFactory.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

final class PersonFactory {

    static func person(
        id: String,
        name: String,
        x: Double,
        y: Double
    ) -> DetectedPerson {

        return DetectedPerson(

            id: UUID(),

            personID: id,

            displayName: name,

            isTracked: true,

            confidence: 0.98,

            lastSeen: Date(),

            heartRate: Int.random(in: 68...82),

            breathingRate: Double.random(in: 13...18),

            motion: .standing,

            position: Coordinate(x: x, y: y),

            isEmergency: false
        )
    }

}
