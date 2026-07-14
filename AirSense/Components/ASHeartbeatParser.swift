//
//  ASHeartbeatParser.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

//
//  ASHeartbeatParser.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

import Foundation

enum ASHeartbeatParser
{
    static func parse(_ text: String) -> ASHeartbeat?
    {
        let lines = text
            .components(separatedBy: .newlines)
            .map { $0.trimmingCharacters(in: .whitespaces) }
            .filter { !$0.isEmpty }

        guard lines.count >= 8 else
        {
            return nil
        }

        guard lines[0] == "HEARTBEAT" else
        {
            return nil
        }

        let state = ASDeviceState(rawValue: lines[1]) ?? .booting

        let uptime = UInt32(
            lines[2].replacingOccurrences(of: "UPTIME=", with: "")
        ) ?? 0

        let heap = UInt32(
            lines[3].replacingOccurrences(of: "HEAP=", with: "")
        ) ?? 0

        let persons = Int(
            lines[4].replacingOccurrences(of: "PERSONS=", with: "")
        ) ?? 0

        let motion = lines[5]
            .replacingOccurrences(of: "MOTION=", with: "")

        let heartRate = Int(
            lines[6]
                .replacingOccurrences(of: "HEART=", with: "")
        ) ?? 0

        let breathing = Int(
            lines[7]
                .replacingOccurrences(of: "BREATH=", with: "")
        ) ?? 0

        return ASHeartbeat(
            state: state,
            uptime: uptime,
            heap: heap,
            persons: persons,
            motion: motion,
            heartRate: heartRate,
            breathing: breathing
        )
    }
}
