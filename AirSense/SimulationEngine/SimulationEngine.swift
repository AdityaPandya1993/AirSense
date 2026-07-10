//
//  SimulationEngine.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class SimulationEngine {

    // MARK: - Properties

    private var timer: Timer?
    
    weak var delegate: SimulationEngineDelegate?
    
    private let stateMachine = SimulationStateMachine()
    
    private let csiGenerator = CSIGenerator()
    
    private let signalBuffer = SignalBuffer()
    
    private let statisticsCalculator = StatisticsCalculator()

    private var human: HumanEntity!

    // MARK: - Start

    func start() {
        
        createHuman()

        timer = Timer.scheduledTimer(
            withTimeInterval: 1.0,
            repeats: true
        ) { [weak self] _ in

            self?.update()
            

        }

    }

    // MARK: - Stop

    func stop() {

        timer?.invalidate()
        timer = nil

    }

}

extension SimulationEngine {

    private func createHuman() {

        human = HumanEntity(

            name: "Aditya",

            position: PositionComponent(position: Coordinate(x: 2, y: 2)),

            heart: HeartComponent(bpm: 72),

            breathing: BreathingComponent(rate: 14),

            motion: MotionComponent(state: .standing),
            
            activity: ActivityComponent(state: .idle)

        )

    }

}

extension SimulationEngine {

    private func update() {
        stateMachine.moveToNextState()
        print("Current State : \(stateMachine.currentState)")
        print(signalBuffer.packets.count)
        
        switch stateMachine.currentState {

        case .idle:

            human.motion.state = .standing
            human.position.position.x = 2
            human.heart.bpm = 0
            human.breathing.rate = 0

        case .personDetected:

            human.motion.state = .standing
            human.heart.bpm = 72
            human.breathing.rate = 14

        case .monitoring:

            human.motion.state = .walking
            human.position.position.x += 0.30
            human.heart.bpm += 1
            human.breathing.rate = 15

        case .gestureDetected:

            human.motion.state = .waving
            human.heart.bpm = 80
            human.breathing.rate = 18

        case .alert:

            human.motion.state = .standing
            human.heart.bpm = 125
            human.breathing.rate = 28

        }

        print("----------------------------")
        print("""
        -------------------------
        State      : \(stateMachine.currentState)
        Motion     : \(human.motion.state)
        Heart BPM  : \(human.heart.bpm)
        Breathing  : \(human.breathing.rate)
        Position   : \(human.position.position)
        -------------------------
        """)
        
        let signal = HumanSignal(
            motion: human.motion.state,
            heartRate: human.heart.bpm,
            breathingRate: human.breathing.rate
        )

        let frame = csiGenerator.generate(signal: signal)

        let allValues = frame.packets.flatMap { $0.subcarriers }

       // let average = allValues.reduce(0, +) / Double(allValues.count)

        let values =
        frame.packets.flatMap {

            $0.subcarriers

        }

        let statistics =
        statisticsCalculator.calculate(
            from: values
        )

        print("""

        Mean : \(String(format: "%.2f", statistics.mean))

        Variance : \(String(format: "%.2f", statistics.variance))

        Std Dev : \(String(format: "%.2f", statistics.standardDeviation))

        Min : \(String(format: "%.2f", statistics.minimum))

        Max : \(String(format: "%.2f", statistics.maximum))

        """)
        
        print("First 10 Subcarriers \(frame.packets.first!.subcarriers.prefix(10))")
        
        

        frame.packets.forEach {
            signalBuffer.append($0)
        }
        
        delegate?.simulationDidUpdate(
            human,
            csiFrame: frame
        )
    }

}
