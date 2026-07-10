//
//  AirTheme.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

enum AirTheme {

    static func setup(view: NSView) {

        view.wantsLayer = true

        view.layer?.backgroundColor =
            AirColor.background.cgColor

    }

}
