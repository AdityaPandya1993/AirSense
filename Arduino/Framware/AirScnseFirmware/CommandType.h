#ifndef COMMAND_TYPE_H
#define COMMAND_TYPE_H

enum class CommandType
{
    Unknown,

    Hello,

    Ping,

    Status,

    StartMonitoring,

    StopMonitoring,

    StartCSI,

    StopCSI,

    Calibrate,

    Reboot
};

#endif