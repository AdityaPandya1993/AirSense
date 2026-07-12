//
//  AASerialParser.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//


import Foundation

final class ASSerialParser
{
    func parseHeartbeat(from json: Data) throws -> DeviceHeartbeat
    {
        return try JSONDecoder().decode(
            DeviceHeartbeat.self,
            from: json
        )
    }
}
