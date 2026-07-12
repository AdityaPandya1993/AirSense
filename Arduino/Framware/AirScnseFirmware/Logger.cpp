#include "Logger.h"
#include "Config.h"

void Logger::begin()
{
    Serial.begin(SERIAL_BAUD_RATE);

    delay(6000);

    Serial.println("Aditya AAAA");
    Serial.println("Aditya BBBBB");
    Serial.println("Aditya CCCC");

    Serial.println();
    Serial.println("================================");
    Serial.println("AirSense Firmware Started");
    Serial.print("Version : ");
    Serial.println(FIRMWARE_VERSION);
    Serial.println("================================");
}

void Logger::info(const String &message)
{
    Serial.print("[INFO] ");
    Serial.println(message);
}

void Logger::warning(const String &message)
{
    Serial.print("[WARNING] ");
    Serial.println(message);
}

void Logger::error(const String &message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}