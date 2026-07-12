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

    private(set) var devices: [ASSerialDevice] = []

    private let port = ASSerialPort()

    weak var delegate: ASSerialDelegate?

    private init() { }
}

// MARK: - Device Discovery

extension ASSerialManager
{
    func discoverDevices()
    {
        devices.removeAll()

        let fileManager = FileManager.default

        let devPath = "/dev"

        guard let items = try? fileManager.contentsOfDirectory(atPath: devPath)
        else
        {
            print("Unable to scan /dev")
            return
        }

        for item in items
        {
            let lower = item.lowercased()

            let isSupported = ASSerialConstants.supportedDevicePrefixes.contains
            {
                lower.contains($0)
            }

            guard isSupported else
            {
                continue
            }
            
            let device = ASSerialDevice(
                portName: item,
                path: "\(devPath)/\(item)",
                vendorID: nil,
                productID: nil,
                manufacturer: nil,
                serialNumber: nil
            )

            devices.append(device)
        }

        print("================================")
        print("Devices Found : \(devices.count)")
        print("================================")

        for device in devices
        {
            print("--------------------------------")
            print("Name : \(device.portName)")
            print("Path : \(device.path)")
        }
    }
}
