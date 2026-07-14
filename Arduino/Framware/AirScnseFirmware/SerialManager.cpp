//
//  SerialManager.cpp
//  AirSense Firmware
//

#include "SerialManager.h"
#include "Config.h"
#include "CommandParser.h"
#include "DeviceController.h"

void SerialManager::begin()
{
    // Future Expansion
}

void SerialManager::processIncomingCommand()
{
    if (!Serial.available())
    {
        return;
    }

    String message = Serial.readStringUntil('\n');
    message.trim();

    CommandType command = CommandParser::parse(message);

    switch (command)
    {
        case CommandType::Ping:

            handlePing();
            break;

        case CommandType::Hello:

            handleHello();
            break;

        case CommandType::Status:

            DeviceController::shared().update();
            sendStatus();
            break;

        default:

            break;
    }
}

void SerialManager::handlePing()
{
    Serial.println("PONG");
}

void SerialManager::handleHello()
{
    Serial.println("HELLO");
    Serial.println(DEVICE_NAME);
    Serial.println(FIRMWARE_VERSION);
    Serial.println("READY");
}

void SerialManager::sendStatus()
{
    DeviceController::shared().update();

    Serial.println("STATUS");

    Serial.println(DeviceController::shared().status());

    Serial.print("UPTIME=");
    Serial.println(DeviceController::shared().uptime());

    Serial.print("HEAP=");
    Serial.println(DeviceController::shared().heap());

    Serial.print("PERSONS=");
    Serial.println(DeviceController::shared().personCount());

    Serial.print("MOTION=");
    Serial.println(DeviceController::shared().motion());

    Serial.print("HEART=");
    Serial.println(DeviceController::shared().heartRate());

    Serial.print("BREATH=");
    Serial.println(DeviceController::shared().breathing());
}

void SerialManager::sendHeartbeat()
{
    DeviceController::shared().update();

    Serial.println("HEARTBEAT");

    Serial.println(DeviceController::shared().status());

    Serial.print("UPTIME=");
    Serial.println(DeviceController::shared().uptime());

    Serial.print("HEAP=");
    Serial.println(DeviceController::shared().heap());

    Serial.print("PERSONS=");
    Serial.println(DeviceController::shared().personCount());

    Serial.print("MOTION=");
    Serial.println(DeviceController::shared().motion());

    Serial.print("HEART=");
    Serial.println(DeviceController::shared().heartRate());

    Serial.print("BREATH=");
    Serial.println(DeviceController::shared().breathing());
}