//
//  SimulationEngine.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

//
//  SimulationEngine.swift
//  AirSense
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

    private var persons: [DetectedPerson] = []
    private var pets: [DetectedPet] = []

    private var human: HumanEntity!

    // MARK: - Start

    func start() {

        persons = [

            PersonFactory.person(
                id: "P001",
                name: "Aditya",
                x: 2,
                y: 2
            ),

            PersonFactory.person(
                id: "P002",
                name: "Guest",
                x: 5,
                y: 2
            )

        ]

        pets = [
            PetFactory.dog()
        ]

        createHuman()

        timer = Timer.scheduledTimer(
            withTimeInterval: 1.0,
            repeats: true
        ) { [weak self] _ in

            self?.update()

        }
    }

    func stop() {

        timer?.invalidate()
        timer = nil
    }
}

// MARK: - Human

extension SimulationEngine {

    private func createHuman() {

        human = HumanEntity(

            name: "Aditya",

            position: PositionComponent(
                position: Coordinate(x: 2, y: 2)
            ),

            heart: HeartComponent(
                bpm: 72
            ),

            breathing: BreathingComponent(
                rate: 14
            ),

            motion: MotionComponent(
                state: .standing
            ),

            activity: ActivityComponent(
                state: .idle
            )
        )
    }
}

// MARK: - Room

extension SimulationEngine {

    private func updateRoom() {

        guard !persons.isEmpty else {
            return
        }

        persons[0].heartRate = human.heart.bpm
        persons[0].breathingRate = human.breathing.rate
        persons[0].motion = human.motion.state
        persons[0].position = human.position.position
        persons[0].lastSeen = Date()
        persons[0].isTracked = true
        persons[0].confidence = 1.0
        persons[0].isEmergency = stateMachine.currentState == .alert

        RoomManager.shared.updatePerson(persons[0])
    }
}

// MARK: - Update

extension SimulationEngine {

    private func update() {

        stateMachine.moveToNextState()

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

        let signal = HumanSignal(
            motion: human.motion.state,
            heartRate: human.heart.bpm,
            breathingRate: human.breathing.rate
        )

        let frame = csiGenerator.generate(signal: signal)

        let values = frame.packets.flatMap {
            $0.subcarriers
        }

        let statistics = statisticsCalculator.calculate(from: values)

        print("""
        Mean : \(statistics.mean)
        Variance : \(statistics.variance)
        Std Dev : \(statistics.standardDeviation)
        """)

        frame.packets.forEach {
            signalBuffer.append($0)
        }

        updateRoom()

        delegate?.simulationDidUpdate(
            human,
            csiFrame: frame
        )
    }
}
