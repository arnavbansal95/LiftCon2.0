#include "comms.h"

void InitComms(bool MB1 = true, bool MB2 = true, bool Wifi = true)
{
    if(MB1 == true)
    {
        digitalWrite(MAX485_1_EN, HIGH);
        Serial2.begin(9600);
    }
    if(MB2 == true)
    {
        digitalWrite(MAX485_2_EN, HIGH);
        Serial2.begin(9600);
    }
}