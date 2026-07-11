//
//  DetectedPet.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//


import Foundation

struct DetectedPet: Identifiable, Equatable {

    let id: UUID

    var petID: String

    var name: String

    var species: PetSpecies

    var position: Coordinate

    var motion: MotionState

    var isTracked: Bool

}
