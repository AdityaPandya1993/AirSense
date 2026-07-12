//
//  ASSerialDevice.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//

import Foundation

struct ASSerialDevice
{
    let portName: String

    let vendorID: Int

    let productID: Int

    let manufacturer: String

    let serialNumber: String?
}
