//
// WindowFunction.h
//

#ifndef WINDOW_FUNCTION_H
#define WINDOW_FUNCTION_H

class WindowFunction
{
public:

    static WindowFunction& shared();

    void apply(
        float* samples,
        int count
    );

private:

    WindowFunction();
};

#endif