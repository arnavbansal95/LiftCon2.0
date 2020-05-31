#include "comms.h"

void InitComms(bool MB1 = true, bool MB2 = true, bool Wifi = true, bool DBG = true)
{
    pinMode(MAX485_1_EN, OUTPUT);
    pinMode(MAX485_2_EN, OUTPUT);
    if(MB1 == true)
    {
        digitalWrite(MAX485_1_EN, LOW);
        Serial2.begin(9600);
    }
    if(MB2 == true)
    {
        digitalWrite(MAX485_2_EN, LOW);
        Serial3.begin(9600);
    }
    if(DBG == true)
    {
        Serial.begin(9600);
    }
}

void SendData(char payload, uint8_t device = 0)
{
    if(device != 0)
    {
        if(device == MB_1)
        {
            digitalWrite(MAX485_1_EN, HIGH);
            Serial2.write(payload);
            digitalWrite(MAX485_1_EN, LOW);
        }
        if(device == MB_2)
        {
            digitalWrite(MAX485_2_EN, HIGH);
            Serial3.write(payload);
            digitalWrite(MAX485_2_EN, LOW);
        }
    }
}

char ReceiveData(uint8_t device = 0)
{
    if(device != 0)
    {
        if(device == MB_1)
        {
            digitalWrite(MAX485_1_EN, LOW);
            if(Serial2.available() > 0)
            {
                return(Serial2.read());
            }
            else
            {
                return(NULL);
            }
        }
        if(device == MB_2)
        {
            digitalWrite(MAX485_2_EN, LOW);
            if(Serial2.available() > 0)
            {
                return(Serial3.read());
            }
            else
            {
                return(NULL);
            }
        }
    }
}