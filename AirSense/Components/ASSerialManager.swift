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
    
    private var listening = false

    private var listeningQueue = DispatchQueue(
        label: "com.airsense.serial.listener"
    )

    weak var delegate: ASSerialDelegate?

    private(set) var isConnected = false

    private init() { }
}

// MARK: - Device Discovery

extension ASSerialManager
{
    
    func startListening()
    {
        guard !listening else
        {
            return
        }

        listening = true

        listeningQueue.async
        {
            while self.listening
            {
                do
                {
                    let text = try self.receive()

                    DispatchQueue.main.async
                    {
                        DispatchQueue.main.async {
                            self.delegate?.serialManager(didReceive: text)
                        }
                    }
                }
                catch
                {
                    // Ignore timeout/read errors for now
                }
            }
        }
    }

    func stopListening()
    {
        listening = false
    }
    
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

// MARK: - Connection

extension ASSerialManager
{
    func connect(to device: ASSerialDevice) throws
    {
        port.configure(devicePath: device.path)

        try port.open()

        isConnected = true

        print("✅ Connected")
    }

    func disconnect()
    {
        stopListening()

        port.close()

        print("🔴 Disconnected")
    }
}

// MARK: - Send

extension ASSerialManager
{
    //this is overload func
    func send(_ command: ASCommand) throws
    {
        try send(command.rawValue)
    }
    
    func send(_ command: String) throws
    {
        print("📤 Sending :", command)

        guard isConnected else
        {
            throw ASSerialError.failedToOpen
        }

        try port.write(Data("\(command)\n".utf8))
    }
}

// MARK: - Receive

extension ASSerialManager
{
    func receive() throws -> String
    {
        let data = try port.read(timeout: 2)

        let text = String(data: data, encoding: .utf8) ?? ""

       
        return text
    }
}


