//
//  Logger.h
//  AirSense Firmware
//

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:

    static void begin();

    static void info(const String& message);

    static void warning(const String& message);

    static void error(const String& message);

};

#endif