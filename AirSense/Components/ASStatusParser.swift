//
//  ASStatusParser.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

import Foundation

enum ASStatusParser
{
    static func parse(_ text: String) -> ASDeviceStatus?
    {
        let lines = text
            .components(separatedBy: .newlines)
            .map { $0.trimmingCharacters(in: .whitespaces) }
            .filter { !$0.isEmpty }

        guard lines.count >= 5 else
        {
            return nil
        }

        guard lines[0] == "STATUS" else
        {
            return nil
        }

        let status = lines[1]

        let uptime = UInt32(
            lines[2].replacingOccurrences(of: "UPTIME=", with: "")
        ) ?? 0

        let heap = UInt32(
            lines[3].replacingOccurrences(of: "HEAP=", with: "")
        ) ?? 0

        let persons = Int(
            lines[4].replacingOccurrences(of: "PERSONS=", with: "")
        ) ?? 0

        return ASDeviceStatus(
            status: status,
            uptime: uptime,
            heap: heap,
            persons: persons
        )
    }
}
