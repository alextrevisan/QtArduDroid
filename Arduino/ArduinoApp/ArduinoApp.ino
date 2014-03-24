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
        char *send = new char[8];

        itoa(analogRead(A0),buf,10);
        strcpy(send,"A0:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        itoa(analogRead(A1),buf,10);
        strcpy(send,"A1:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        itoa(analogRead(A2),buf,10);
        strcpy(send,"A2:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        itoa(analogRead(A3),buf,10);
        strcpy(send,"A3:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        itoa(analogRead(A4),buf,10);
        strcpy(send,"A4:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        itoa(analogRead(A5),buf,10);
        strcpy(send,"A5:");
        strcpy(send+3,buf);
        connection->write(strlen(send),(uint8_t*)send);
        delay(10);
        ADB::poll();

        lastTime = millis();

        delete[] send;
    }


}
