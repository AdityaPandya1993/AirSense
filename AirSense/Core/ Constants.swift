//
//   Constants.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

enum Constants {

    enum Timer {

        static let dashboardRefresh: TimeInterval = 2.0

    }

    enum HeartRate {

        static let minimum = 60
        static let maximum = 100

    }

    enum Signal {

        static let excellent = "Excellent"
        static let good = "🟡 Good"
        static let weak = "Weak"

    }

}
