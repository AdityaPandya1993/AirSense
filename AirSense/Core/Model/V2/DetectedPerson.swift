//
//  DetectedPerson.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

struct DetectedPerson: Identifiable, Equatable {

    // MARK: - Identity

    let id: UUID

    var personID: String
    var displayName: String

    // MARK: - Tracking

    var isTracked: Bool
    var confidence: Double
    var lastSeen: Date

    // MARK: - Health

    var heartRate: Int
    var breathingRate: Double

    // MARK: - Activity

    var motion: MotionState

    // MARK: - Position

    var position: Coordinate

    // MARK: - Emergency

    var isEmergency: Bool

}

// MARK: - Default

extension DetectedPerson {

    static let unknown = DetectedPerson(
        id: UUID(),
        personID: "P001",
        displayName: "Unknown",
        isTracked: false,
        confidence: 0,
        lastSeen: Date(),
        heartRate: 0,
        breathingRate: 0,
        motion: MotionState.standing,
        position: Coordinate(x: 0, y: 0),
        isEmergency: false
    )

}
