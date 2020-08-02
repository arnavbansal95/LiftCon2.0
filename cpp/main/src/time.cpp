#include "time.h"

void InitTime(void)
{
    startMillis = millis();
    static bool newChipset = true;   
    for (int i=0;i<EEPROM.length()-1;i++) 
    {
        if((EEPROM.read(i) != EEPROM.read(i+1)) || (EEPROM.read(i) != 255))
        {
            newChipset = false;
        }
    }
    if(newChipset)
    {
        Serial.println("New Chipset Detected!");
        for (int i=0;i<EEPROM.length();i++) 
        {   
            EEPROM.write(i, 0);
        }   
    }
    else
    {
        GetTime();
        Serial.print("ElapsedTime till now: ");
        Serial.print(elapsedDays);
        Serial.print(":");
        Serial.println(elapsedHours);
    }
    
}

void SetTime(void)
{
    static unsigned long currentMillis;
    currentMillis = millis();
    elapsedSeconds = (currentMillis - startMillis) / 1000;
    if((elapsedSeconds % 60 == 0) && (elapsedSeconds > 0))
    {
        elapsedMins += elapsedSeconds / 60;
        startMillis = millis();
    }
    if(elapsedMins % 60 == 0)
    {
        elapsedHours += elapsedMins / 60;
        elapsedMins = 0;
    }
    if(elapsedHours % 24 == 0)
    {
        elapsedDays += elapsedHours / 24;
        elapsedHours = 0;
    }
}

void WriteTime(void)
{
    EEPROM.write(HOURS_EEPROM_RES, elapsedHours);
    EEPROM.write(DAYS_EEPROM_RES, elapsedDays);
}

void GetTime(void)
{
    elapsedHours = EEPROM.read(HOURS_EEPROM_RES);
    elapsedDays = EEPROM.read(DAYS_EEPROM_RES);
}

void ShutDown(mode_t* mode)
{
    GetTime();
    if(elapsedHours == 5)
    {
        *mode = SHUTDOWN;
    }
}