//
//  AppConfiguration.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class AppConfiguration {

    static let shared = AppConfiguration()

    private init() { }

    var mode: AppMode = .simulation

}
