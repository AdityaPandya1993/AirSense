//
//  HumanEntities.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Foundation

final class HumanEntity: Entity {

    var position: PositionComponent

    var heart: HeartComponent

    var breathing: BreathingComponent

    var motion: MotionComponent
    
    var activity: ActivityComponent

    init(
        name: String,
        position: PositionComponent,
        heart: HeartComponent,
        breathing: BreathingComponent,
        motion: MotionComponent,
        activity : ActivityComponent
    ) {

        self.position = position
        self.heart = heart
        self.breathing = breathing
        self.motion = motion
        self.activity = activity

        super.init(name: name)
    }

}
