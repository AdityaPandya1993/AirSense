//
//  DetectedPerson.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation
import CoreGraphics

struct DetectedPerson: Identifiable {

    let id: UUID

    var heartRate: Int

    var breathingRate: Double

    var position: CGPoint

    var confidence: Double

    init(
        id: UUID = UUID(),
        heartRate: Int,
        breathingRate: Double,
        position: CGPoint,
        confidence: Double
    ) {

        self.id = id
        self.heartRate = heartRate
        self.breathingRate = breathingRate
        self.position = position
        self.confidence = confidence
    }

}
