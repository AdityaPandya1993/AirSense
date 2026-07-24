//
// MatrixV1.cpp
// AirSense Firmware
//

#include "MatrixV1.h"

////////////////////////////////////////////////////////

MatrixV1::MatrixV1()
{
    _rows = 0;
    _cols = 0;

    clear();
}

////////////////////////////////////////////////////////

void MatrixV1::create(
    uint16_t rows,
    uint16_t cols
)
{
    _rows = rows;
    _cols = cols;

    clear();
}

////////////////////////////////////////////////////////

void MatrixV1::clear()
{
    for(uint16_t r=0;r<MAX_SIZE;r++)
    {
        for(uint16_t c=0;c<MAX_SIZE;c++)
        {
            _data[r][c]=0.0f;
        }
    }
}

////////////////////////////////////////////////////////

float MatrixV1::get(
    uint16_t row,
    uint16_t col
) const
{
    return _data[row][col];
}

////////////////////////////////////////////////////////

void MatrixV1::set(
    uint16_t row,
    uint16_t col,
    float value
)
{
    _data[row][col]=value;
}

////////////////////////////////////////////////////////

uint16_t MatrixV1::rows() const
{
    return _rows;
}

////////////////////////////////////////////////////////

uint16_t MatrixV1::cols() const
{
    return _cols;
}

////////////////////////////////////////////////////////

float* MatrixV1::raw()
{
    return &_data[0][0];
}