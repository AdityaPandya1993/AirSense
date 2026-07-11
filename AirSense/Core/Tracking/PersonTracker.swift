//
//  PersonTracker.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 11/07/26.
//

import Foundation

final class PersonTracker {

    // MARK: - Persons

    private(set) var persons: [DetectedPerson] = []

    // MARK: - Add

    func add(_ person: DetectedPerson) {

        guard !persons.contains(where: { $0.personID == person.personID }) else {
            return
        }

        persons.append(person)

    }

    // MARK: - Update

    func update(_ person: DetectedPerson) {

        guard let index = persons.firstIndex(where: {
            $0.personID == person.personID
        }) else {
            return
        }

        persons[index] = person

    }

    // MARK: - Remove

    func remove(personID: String) {

        persons.removeAll {
            $0.personID == personID
        }

    }

    // MARK: - Find

    func person(id: String) -> DetectedPerson? {

        persons.first {
            $0.personID == id
        }

    }

}
