//
//  RoomManager.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

final class RoomManager {

    // MARK: - Singleton

    static let shared = RoomManager()

    private init() { }

    // MARK: - Managers

    let personTracker = PersonTracker()

    // Future
    // let petTracker = PetTracker()
    // let csiManager = CSIManager()
    // let emergencyManager = EmergencyManager()

    // MARK: - Room

    private(set) var room = RoomModel.empty

}

// MARK: - Person

extension RoomManager {

    func addPerson(_ person: DetectedPerson) {

        personTracker.add(person)

        room.persons = personTracker.persons

        updateRoomState()

    }

    func updatePerson(_ person: DetectedPerson) {

        personTracker.update(person)

        room.persons = personTracker.persons

        updateRoomState()

    }

}

private extension RoomManager {

    func updateRoomState() {

        if room.persons.isEmpty {

            room.roomState = .empty

        } else {

            room.roomState = .occupied

        }

    }

}
