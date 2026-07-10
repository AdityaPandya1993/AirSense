//
//  WaveGraphView.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation
import Cocoa

final class WaveGraphView: NSView {

    // MARK: - Properties

    private var samples: [Double] = []
    private let maxSamples = 200
    private var displayTimer: Timer?

    var lineColor: NSColor = .systemGreen {
        didSet { needsDisplay = true }
    }

    var lineWidth: CGFloat = 2 {
        didSet { needsDisplay = true }
    }
    
    override func awakeFromNib() {

        super.awakeFromNib()

        displayTimer = Timer.scheduledTimer(
            withTimeInterval: 1.0 / 60.0,
            repeats: true
        ) { [weak self] _ in

            self?.needsDisplay = true

        }

    }
    
    deinit {

        displayTimer?.invalidate()

    }

    // MARK: - Update

    func update(samples: [Double]) {

        self.samples = samples

        if self.samples.count > maxSamples {

            self.samples = Array(
                self.samples.suffix(maxSamples)
            )

        }

        needsDisplay = true

    }
    
    func append(sample: Double) {

        samples.append(sample)

        if samples.count > maxSamples {

            samples.removeFirst()

        }
    }

    // MARK: - Draw

    override func draw(_ dirtyRect: NSRect) {

        super.draw(dirtyRect)

        guard samples.count > 1 else { return }

        NSColor.clear.setFill()
        dirtyRect.fill()

        let path = NSBezierPath()
        path.lineWidth = lineWidth

        let width = bounds.width
        let height = bounds.height

        let minValue = -50.0
        let maxValue = -20.0
        let range = maxValue - minValue

        for (index, value) in samples.enumerated() {

            let x = CGFloat(index) / CGFloat(samples.count - 1) * width

            let normalized = (value - minValue) / range

            let y = height - CGFloat(normalized) * height

            let point = CGPoint(x: x, y: y)

            if index == 0 {
                path.move(to: point)
            } else {
                path.line(to: point)
            }

        }
        
        

        lineColor.setStroke()
        print("Drawing : \(samples.count)")
        path.stroke()

    }

}
