//
//  ActivityComponent.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

enum ActivityState {

    case idle

    case monitoring

    case gesture

    case sleeping

    case emergency

    case leaving

}


struct ActivityComponent {

    var state: ActivityState

}
