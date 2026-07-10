//
//  SignalBuffer.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

//
// SignalBuffer.swift
//

import Foundation

final class SignalBuffer {

    private(set) var packets: [CSIPacket] = []

    var maxPackets: Int = 10

    func append(_ packet: CSIPacket) {

        packets.append(packet)

        if packets.count > maxPackets {
            packets.removeFirst()
        }
    }

    func clear() {
        packets.removeAll()
    }

}
