//
//  ASSerialManager.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//


import Foundation

final class ASSerialManager
{
    // MARK: - Singleton

    static let shared = ASSerialManager()

    // MARK: - Properties

    private(set) var isConnected = false

    private init() { }

    // MARK: - Public

    func start()
    {
        print("================================")
        print("AirSense Serial Manager Started")
        print("================================")
    }

    func stop()
    {
        print("AirSense Serial Manager Stopped")
    }
}
