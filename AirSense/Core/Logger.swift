//
//  Logger.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class Logger {

    static let shared = Logger()

    private init() {}

    func log(_ message: String) {

        let formatter = DateFormatter()
        formatter.dateFormat = "HH:mm:ss"

        let time = formatter.string(from: Date())

        print("[\(time)] \(message)")
    }
}
