//
//  SimulationTest.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class SimulationTest {

    func createHuman() {

        let human = HumanEntity(

            name: "Aditya",

            position: PositionComponent(
                position: Coordinate(x: 2.0, y: 3.0)
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
            activity: ActivityComponent (state: .idle)
        )

        print("Human : \(human.name)")
        print("Heart : \(human.heart.bpm)")
        print("Breathing : \(human.breathing.rate)")
        print("Position : \(human.position.position)")
        print("Motion : \(human.motion.state)")
    }

}
