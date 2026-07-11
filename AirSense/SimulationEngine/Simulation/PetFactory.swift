//
//  PetFactory.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

final class PetFactory {

    static func dog() -> DetectedPet {

        DetectedPet(

            id: UUID(),

            petID: "DOG001",

            name: "Buddy",

            species: .dog,

            position: Coordinate(x: 5, y: 3),

            motion: .walking,

            isTracked: true
        )

    }

}
