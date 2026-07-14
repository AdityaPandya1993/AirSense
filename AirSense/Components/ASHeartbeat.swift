//
//  ASHeartbeat.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 13/07/26.
//

import Foundation

struct ASHeartbeat
{
    let state: ASDeviceState
    let uptime: UInt32
    let heap: UInt32
    let persons: Int

    let motion: String
    let heartRate: Int
    let breathing: Int
}

