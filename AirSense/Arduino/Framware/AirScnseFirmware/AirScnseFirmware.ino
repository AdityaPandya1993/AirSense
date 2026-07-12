void setup()
{
    Serial.begin(115200);

    delay(3000);

    Serial.println("HELLO");
}

void loop()
{
    Serial.println("RUNNING");
    delay(1000);
}