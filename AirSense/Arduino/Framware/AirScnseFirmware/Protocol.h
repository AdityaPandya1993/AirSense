//
//  Protocol.h
//  AirSense Firmware
//
//  AirSense Serial Protocol v1
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

//==================================================
// Packet
//==================================================

#define ASP_BEGIN          "BEGIN"
#define ASP_END            "END"

//==================================================
// Keys
//==================================================

#define ASP_DEVICE         "DEVICE"
#define ASP_FIRMWARE       "FW"
#define ASP_STATUS         "STATUS"
#define ASP_UPTIME         "UPTIME"
#define ASP_HEAP           "HEAP"

#define ASP_PERSONS        "PERSONS"
#define ASP_DOGS           "DOGS"

#define ASP_HEART          "HEART"
#define ASP_BREATH         "BREATH"

#define ASP_ROOM_TEMP      "ROOM_TEMP"

#endif