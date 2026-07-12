//
//  ASSerialPort.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//

import Foundation
import Darwin

final class ASSerialPort
{
    // MARK: - Properties

    private(set) var devicePath: String?

    private(set) var fileDescriptor: Int32 = -1

    var isOpen: Bool
    {
        return fileDescriptor >= 0
    }

    // MARK: - Init

    init()
    {

    }
}

// MARK: - Configuration

extension ASSerialPort
{
    func configure(devicePath: String)
    {
        self.devicePath = devicePath
    }
    
    private func configurePort() throws
    {
        var options = termios()

        guard tcgetattr(fileDescriptor, &options) == 0 else
        {
            throw ASSerialError.invalidConfiguration
        }

        cfmakeraw(&options)

        // Read timeout
//        options.c_cc[VMIN] = 0
//        options.c_cc[VTIME] = 10

        let baud = baudRateValue(ASSerialConstants.baudRate)

        cfsetispeed(&options, baud)
        cfsetospeed(&options, baud)

        options.c_cflag |= tcflag_t(CLOCAL | CREAD)
        options.c_cflag &= ~tcflag_t(PARENB)
        options.c_cflag &= ~tcflag_t(CSTOPB)
        options.c_cflag &= ~tcflag_t(CSIZE)
        options.c_cflag |= tcflag_t(CS8)

        guard tcsetattr(fileDescriptor, TCSANOW, &options) == 0 else
        {
            throw ASSerialError.invalidConfiguration
        }
    }
}

// MARK: - Public

extension ASSerialPort
{
    func open() throws
    {
        guard let devicePath else
        {
            throw ASSerialError.deviceNotFound
        }

        print("Opening :", devicePath)

        let descriptor = Darwin.open(devicePath, O_RDWR | O_NOCTTY)

        if descriptor < 0
        {
            let code = errno

            print("errno =", code)
            print(String(cString: strerror(code)))

            throw ASSerialError.failedToOpen
        }

        fileDescriptor = descriptor
        try configurePort()
    }

    func close()
    {
        guard isOpen else
        {
            return
        }

        Darwin.close(fileDescriptor)

        fileDescriptor = -1
    }

    func read(timeout: TimeInterval = 2.0) throws -> Data
    {
        guard isOpen else
        {
            throw ASSerialError.readFailed
        }

        var received = Data()

        let start = Date()

        while Date().timeIntervalSince(start) < timeout
        {
            var buffer = [UInt8](repeating: 0, count: 256)

            let count = Darwin.read(
                fileDescriptor,
                &buffer,
                buffer.count
            )

            if count > 0
            {
                received.append(buffer, count: count)

                if received.contains(10)   // '\n'
                {
                    break
                }
            }

            usleep(10000)
        }

        guard !received.isEmpty else
        {
            throw ASSerialError.readFailed
        }

        return received
    }

    func write(_ data: Data) throws
    {
        guard isOpen else
        {
            throw ASSerialError.writeFailed
        }

        let result = data.withUnsafeBytes
        {
            Darwin.write(
                fileDescriptor,
                $0.baseAddress,
                data.count
            )
        }

        guard result == data.count else
        {
            throw ASSerialError.writeFailed
        }
    }
}

// MARK: - Private

private extension ASSerialPort
{
    func baudRateValue(_ baudRate: Int) -> speed_t
    {
        switch baudRate
        {
        case 9600:
            return speed_t(B9600)

        case 19200:
            return speed_t(B19200)

        case 38400:
            return speed_t(B38400)

        case 57600:
            return speed_t(B57600)

        case 115200:
            return speed_t(B115200)

        default:
            return speed_t(B115200)
        }
    }
}


