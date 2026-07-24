//
// MatrixV1.h
// AirSense Firmware
//

#ifndef MATRIX_V1_H
#define MATRIX_V1_H

#include <Arduino.h>

class MatrixV1
{
public:

    MatrixV1();

    void create(
        uint16_t rows,
        uint16_t cols
    );

    void clear();

    float get(
        uint16_t row,
        uint16_t col
    ) const;

    void set(
        uint16_t row,
        uint16_t col,
        float value
    );

    uint16_t rows() const;

    uint16_t cols() const;

    float* raw();

private:

    uint16_t _rows;

    uint16_t _cols;

    static constexpr uint16_t MAX_SIZE = 32;

    float _data[MAX_SIZE][MAX_SIZE];

};

#endif