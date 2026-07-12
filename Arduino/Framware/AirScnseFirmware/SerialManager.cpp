//
//  SerialManager.cpp
//  AirSense Firmware
//

#include "SerialManager.h"

void SerialManager::begin()
{
    // Future Expansion
}

void SerialManager::sendHeartbeat(
    const HeartbeatPacket& packet
)
{
    Serial.print("{");

    Serial.print("\"type\":\"heartbeat\",");

    Serial.print("\"device\":\"");
    Serial.print(packet.deviceName);
    Serial.print("\",");

    Serial.print("\"firmware\":\"");
    Serial.print(packet.firmwareVersion);
    Serial.print("\",");

    Serial.print("\"status\":\"");
    Serial.print(packet.status);
    Serial.print("\",");

    Serial.print("\"uptime\":");
    Serial.print(packet.uptime);
    Serial.print(",");

    Serial.print("\"heap\":");
    Serial.print(packet.freeHeap);

    Serial.println("}");
}