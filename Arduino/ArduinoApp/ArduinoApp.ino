#include <Arduino.h>
#include <SPI.h>
#include <Adb.h>

Connection * connection;
long lastTime;
float getVoltage(int pin);

void adbEventHandler(Connection * connection, adb_eventType event, uint16_t length, uint8_t * data)
{

}

void setup()
{
    Serial.begin(57600);

    lastTime = millis();

    ADB::init();

    connection = ADB::addConnection("tcp:4568", true, adbEventHandler);
}

void loop()
{
    if ((millis() - lastTime) > 100)
    {
        char buf[5];
        itoa(analogRead(A0),buf,10);

        connection->write(strlen(buf),(uint8_t*)&buf);
        Serial.println(buf);

        lastTime = millis();
    }

    ADB::poll();
}
