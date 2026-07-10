//
//  GlowAnimator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

final class GlowAnimator {

    static func glow(view: NSView) {

        guard let layer = view.layer else { return }

        let animation = CABasicAnimation(keyPath: "shadowOpacity")

        animation.fromValue = 0.2
        animation.toValue = 0.6
        animation.duration = 0.30
        animation.autoreverses = true

        layer.add(animation,
                  forKey: "glow")

    }

}
