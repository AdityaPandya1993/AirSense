#include "CommandParser.h"

CommandType CommandParser::parse(const String& command)
{
    if (command == "HELLO")
        return CommandType::Hello;

    if (command == "PING")
        return CommandType::Ping;

    if (command == "STATUS")
        return CommandType::Status;

    if (command == "START_MONITORING")
        return CommandType::StartMonitoring;

    if (command == "STOP_MONITORING")
        return CommandType::StopMonitoring;

    if (command == "START_CSI")
        return CommandType::StartCSI;

    if (command == "STOP_CSI")
        return CommandType::StopCSI;

    if (command == "CALIBRATE")
        return CommandType::Calibrate;

    if (command == "REBOOT")
        return CommandType::Reboot;

    return CommandType::Unknown;
}