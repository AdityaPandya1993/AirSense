//
//  DebugConsole.h
//  AirSense Firmware
//
//  Version : 1.0
//

#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

class DebugConsole
{
public:

    static DebugConsole& shared();

    void printDSP();

private:

    DebugConsole();
};

#endif