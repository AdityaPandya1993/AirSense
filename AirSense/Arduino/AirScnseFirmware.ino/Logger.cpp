//
//  Logger.cpp
//  AirSense Firmware
//

#include "Logger.h"
#include "Config.h"

void Logger::begin()
{
    Serial.begin(SERIAL_BAUD_RATE);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println();
    Serial.println("================================");
    Serial.println("AirSense Firmware Started");
    Serial.println("Version : " FIRMWARE_VERSION);
    Serial.println("================================");
}

void Logger::info(const String& message)
{
    Serial.print("[INFO] ");
    Serial.println(message);
}

void Logger::warning(const String& message)
{
    Serial.print("[WARNING] ");
    Serial.println(message);
}

void Logger::error(const String& message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}