//
//  RoomModel.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

struct RoomModel {

    // MARK: - Room

    var roomID: String

    var roomName: String

    // MARK: - Occupants

    var persons: [DetectedPerson]

    // MARK: - Pets

    var pets: [DetectedPet]

    // MARK: - Environment

    var temperature: Double

    var humidity: Double

    // MARK: - Status

    var roomState: RoomState

    var emergencyState: EmergencyState

}

extension RoomModel {

    static let empty = RoomModel(

        roomID: "ROOM-001",

        roomName: "Living Room",

        persons: [],

        pets: [],

        temperature: 27,

        humidity: 55,

        roomState: .empty,

        emergencyState: .none

    )

}
