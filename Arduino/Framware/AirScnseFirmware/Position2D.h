//
//  Position2D.h
//  AirSense Firmware
//
//  Module-04
//

#ifndef POSITION2D_H
#define POSITION2D_H

struct Position2D
{
    float x;
    float y;

    Position2D()
        : x(0.0f),
          y(0.0f)
    {
    }

    Position2D(
        float xValue,
        float yValue
    )
        : x(xValue),
          y(yValue)
    {
    }
};

#endif