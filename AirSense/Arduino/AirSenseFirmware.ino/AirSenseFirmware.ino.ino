/*
------------------------------------
 AirSense Firmware v0.1.0
 Hardware : ESP32-S3
------------------------------------
*/

#define FW_VERSION "0.1.0"

unsigned long lastHeartbeat = 0;

void printBootInformation()
{
    Serial.println();
    Serial.println("====================================");
    Serial.println("      AirSense Firmware");
    Serial.println("====================================");

    Serial.print("Firmware : ");
    Serial.println(FW_VERSION);

    Serial.print("Chip : ");
    Serial.println(ESP.getChipModel());

    Serial.print("Revision : ");
    Serial.println(ESP.getChipRevision());

    Serial.print("CPU Frequency : ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");

    Serial.print("Flash Size : ");
    Serial.print(ESP.getFlashChipSize() / 1024 / 1024);
    Serial.println(" MB");

    Serial.print("Free Heap : ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" Bytes");

    Serial.println("====================================");
    Serial.println();
}

void sendHeartbeat()
{
    Serial.println("----- HEARTBEAT -----");

    Serial.print("Uptime : ");
    Serial.print(millis() / 1000);
    Serial.println(" sec");

    Serial.print("Free Heap : ");
    Serial.println(ESP.getFreeHeap());

    Serial.println("---------------------");
    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    printBootInformation();
}

void loop()
{
    if (millis() - lastHeartbeat >= 1000)
    {
        lastHeartbeat = millis();

        sendHeartbeat();
    }
}