#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <Arduino.h>
#include "CommandType.h"

class CommandParser
{
public:

    static CommandType parse(const String& command);
};

#endif