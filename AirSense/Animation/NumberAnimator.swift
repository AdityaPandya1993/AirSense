//
//  NumberAnimator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

final class NumberAnimator {

    static func animate(label: NSTextField,
                        newValue: String) {

        NSAnimationContext.runAnimationGroup { context in

            context.duration = 0.18

            label.animator().alphaValue = 0.3

        } completionHandler: {

            label.stringValue = newValue

            NSAnimationContext.runAnimationGroup { context in

                context.duration = 0.18

                label.animator().alphaValue = 1

            }

        }

    }

}
