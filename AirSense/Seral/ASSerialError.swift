//
//  ASSerialError.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//


import Foundation

enum ASSerialError: LocalizedError
{
    case deviceNotFound
    case deviceAlreadyOpen
    case failedToOpen
    case failedToClose
    case readFailed
    case writeFailed
    case invalidConfiguration
    case permissionDenied
    case disconnected
    case unknown(Error)

    var errorDescription: String?
    {
        switch self
        {
        case .deviceNotFound:
            return "Serial device not found."

        case .deviceAlreadyOpen:
            return "Serial device is already open."

        case .failedToOpen:
            return "Unable to open serial device."

        case .failedToClose:
            return "Unable to close serial device."

        case .readFailed:
            return "Failed to read serial data."

        case .writeFailed:
            return "Failed to write serial data."

        case .invalidConfiguration:
            return "Invalid serial configuration."

        case .permissionDenied:
            return "Permission denied while accessing serial device."

        case .disconnected:
            return "Serial device disconnected."

        case .unknown(let error):
            return error.localizedDescription
        }
    }
}
