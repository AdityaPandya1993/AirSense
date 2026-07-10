//
//  SimulationStateMachine.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class SimulationStateMachine {

    private(set) var currentState: SimulationState = .idle

    func moveToNextState() {

        switch currentState {

        case .idle:
            currentState = .personDetected

        case .personDetected:
            currentState = .monitoring

        case .monitoring:
            currentState = .gestureDetected

        case .gestureDetected:
            currentState = .alert

        case .alert:
            currentState = .idle
        }
    }

}
