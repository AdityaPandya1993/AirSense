//
//  StatisticsCalculator.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 10/07/26.
//

import Foundation

final class StatisticsCalculator {

    func calculate(
        from values: [Double]
    ) -> Statistics {

        let mean =
            values.reduce(0,+) /
            Double(values.count)

        let variance =
            values
            .map {

                pow($0 - mean, 2)

            }
            .reduce(0,+) /
            Double(values.count)

        let std =
            sqrt(variance)

        return Statistics(

            mean: mean,

            variance: variance,

            standardDeviation: std,

            minimum: values.min() ?? 0,

            maximum: values.max() ?? 0

        )

    }

}
