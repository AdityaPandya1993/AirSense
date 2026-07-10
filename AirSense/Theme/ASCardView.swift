//
//  ASCardView.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation
import Cocoa

@IBDesignable
class ASCardView: NSView {

    // MARK: - Inspectable Properties

    @IBInspectable var cornerRadius: CGFloat = 15.0 {
        didSet {
            updateUI()
        }
    }

    @IBInspectable var borderWidth: CGFloat = 0 {
        didSet {
            updateUI()
        }
    }

    @IBInspectable var borderColor: NSColor = NSColor(calibratedWhite: 0.25, alpha: 1) {
        didSet {
            updateUI()
        }
    }

    @IBInspectable var cardColor: NSColor = NSColor(calibratedWhite: 0.18, alpha: 1) {
        didSet {
            updateUI()
        }
    }

    // MARK: - Init
    
    private let statusView = NSView()

    override func awakeFromNib() {
        super.awakeFromNib()

        setupView()
    }
    
    

    override func prepareForInterfaceBuilder() {
        super.prepareForInterfaceBuilder()

        setupView()
    }
    
    func apply(status: HealthStatus) {

        let color: NSColor

        switch status {

        case .normal:
            color = .systemGreen

        case .warning:
            color = .systemOrange

        case .critical:
            color = .systemRed
        }

        statusView.layer?.backgroundColor = color.cgColor
    }

    // MARK: - Setup
    
    private func setupView() {

        wantsLayer = true

        // Left Status Bar
        statusView.wantsLayer = true
        statusView.translatesAutoresizingMaskIntoConstraints = false
        addSubview(statusView)

        NSLayoutConstraint.activate([
            statusView.leadingAnchor.constraint(equalTo: leadingAnchor),
            statusView.topAnchor.constraint(equalTo: topAnchor),
            statusView.bottomAnchor.constraint(equalTo: bottomAnchor),
            statusView.widthAnchor.constraint(equalToConstant: 6)
        ])

        updateUI()
    }

    private func updateUI() {

        wantsLayer = true

        layer?.cornerRadius = cornerRadius
        layer?.borderWidth = borderWidth
        layer?.borderColor = AirColor.border.cgColor
        layer?.backgroundColor = AirColor.card.cgColor

        layer?.masksToBounds = false

        layer?.shadowColor = NSColor.black.cgColor
        layer?.shadowOpacity = 0.20
        layer?.shadowOffset = CGSize(width: 0, height: 4)
        layer?.shadowRadius = 12

        statusView.layer?.backgroundColor = NSColor.systemGray.cgColor
    }

}
