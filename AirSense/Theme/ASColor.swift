import Cocoa

enum AirColor {

    // MARK: Background

    static let background = NSColor(
        red: 28/255,
        green: 28/255,
        blue: 30/255,
        alpha: 1
    )

    static let card = NSColor(
        red: 42/255,
        green: 42/255,
        blue: 45/255,
        alpha: 1
    )

    static let border = NSColor(
        red: 60/255,
        green: 60/255,
        blue: 65/255,
        alpha: 1
    )

    // MARK: Text

    static let title = NSColor.white

    static let subtitle = NSColor.lightGray

    // MARK: Status

    static let success = NSColor.systemGreen

    static let warning = NSColor.systemOrange

    static let danger = NSColor.systemRed

    static let info = NSColor.systemBlue

}
