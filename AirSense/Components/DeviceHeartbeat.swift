//
//  DeviceHeartbeat.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//

import Foundation

struct DeviceHeartbeat: Codable
{
    let type: String

    let device: String

    let firmware: String

    let status: String

    let uptime: UInt32

    let heap: UInt32
}
