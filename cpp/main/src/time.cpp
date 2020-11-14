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
        Serial.print((uint16_t)((uint16_t)(255 * elapsedDays2) + elapsedDays));
        Serial.print(":");
        Serial.print(elapsedHours);
        Serial.print(":");
        Serial.print(elapsedMins);
        Serial.print(":");
        Serial.println(elapsedSeconds);
        randomSeed(elapsedMins + elapsedSeconds);
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
        elapsedDaysCalc = elapsedHours / 24;
        if((uint16_t)(elapsedDays + elapsedDaysCalc) > 255)
        {
            elapsedDays2 += (((elapsedHours / 24) / 255) + 1);
            elapsedDays = 0; 
        } 
        elapsedDays += elapsedHours / 24;
        elapsedHours = 0;
    }
    writeInterlock = 1;
}

void WriteTime(void)
{
    if(writeInterlock == 1)
    {
        Serial.print("  Writing TimeStamp: ");
        Serial.print((uint16_t)((uint16_t)(255 * elapsedDays2) + elapsedDays));
        Serial.print(":");
        Serial.print(elapsedHours);
        Serial.print(":");
        Serial.print(elapsedMins);
        Serial.print(":");
        Serial.println(elapsedSeconds);
        EEPROM.write(DAYS_EEPROM_RES, elapsedDays);
        EEPROM.write(DAYS2_EEPROM_RES, elapsedDays2);
        EEPROM.write(HOURS_EEPROM_RES, elapsedHours);
        EEPROM.write(MINS_EEPROM_RES, elapsedMins);
        EEPROM.write(SECONDS_EEPROM_RES, elapsedSeconds);
        writeInterlock = 0;
    }
}

void ResetTime(void)
{
    Serial.println("  Resetting TimeStamp: 0:0:0:0");
    EEPROM.write(DAYS_EEPROM_RES, 255);
    EEPROM.write(DAYS2_EEPROM_RES, 0);
    EEPROM.write(HOURS_EEPROM_RES, 23);
    EEPROM.write(MINS_EEPROM_RES, 59);
    EEPROM.write(SECONDS_EEPROM_RES, 0);
}

void GetTime(void)
{
    elapsedDays = EEPROM.read(DAYS_EEPROM_RES);
    elapsedDays2 = EEPROM.read(DAYS2_EEPROM_RES);
    elapsedHours = EEPROM.read(HOURS_EEPROM_RES);
    elapsedMins = EEPROM.read(MINS_EEPROM_RES);
    elapsedSeconds = EEPROM.read(SECONDS_EEPROM_RES);
}

void CheckShutDown(mode_t* mode)
{
    GetTime();
    uint16_t days = (255 * elapsedDays2) + elapsedDays;
    uint8_t hours = elapsedHours;
    uint16_t days_check = (uint16_t)random(370, 400);
    uint8_t hours_check = (uint8_t)random(6, 12);
    if((days >= days_check) && (hours >= hours_check))
    {
        *mode = SHUTDOWN;
    }
}