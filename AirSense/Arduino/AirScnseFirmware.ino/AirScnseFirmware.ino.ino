#include "Config.h"
#include "Logger.h"

unsigned long lastHeartbeat = 0;

void setup()
{
    Logger::begin();

    Logger::info("Boot Complete");
}

void loop()
{
    if (millis() - lastHeartbeat >= HEARTBEAT_INTERVAL)
    {
        lastHeartbeat = millis();

        Logger::info(
            "Free Heap : " + String(ESP.getFreeHeap())
        );
    }
}