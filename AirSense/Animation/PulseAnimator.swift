//
//  PulseAnimator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

final class PulseAnimator {

    static func pulse(view: NSView) {

        guard let layer = view.layer else { return }

        let animation = CABasicAnimation(keyPath: "transform.scale")

        animation.fromValue = 1

        animation.toValue = 1.05

        animation.duration = 0.15

        animation.autoreverses = true

        layer.add(animation,
                  forKey: "pulse")

    }

}
