//
//  Config.h
//  AirSense Firmware
//
//  Version : 0.2.0
//

#ifndef CONFIG_H
#define CONFIG_H

//--------------------------------------------------
// WiFi
//--------------------------------------------------

#define WIFI_SSID       "Jackspeed 4G"
#define WIFI_PASSWORD   "JACKSPEED_"

#include <Arduino.h>

//==================================================
// Device
//==================================================

#define DEVICE_NAME            "AirSense ESP32-S3"
#define DEVICE_MODEL           "ESP32-S3"

//==================================================
// Firmware
//==================================================

#define FIRMWARE_VERSION       "0.2.0"

//==================================================
// Serial
//==================================================

#define SERIAL_BAUD_RATE       115200

//==================================================
// Heartbeat
//==================================================

#define HEARTBEAT_INTERVAL     1000

#endif