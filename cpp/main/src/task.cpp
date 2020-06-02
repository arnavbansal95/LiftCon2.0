#include "task.h"

int taskVar_mode = -1;                              // mode = 0: Auto Mode, 
                                                    // mode = 1: Manual Mode, 
                                                    // mode = 2: Reset, 
                                                    // mode = -1: Start State
unsigned long previousMillis[2] = {0, 0};           // will store last time 
unsigned long currentMillis[2];                     // will store current time
const long interval = 5000;                         // interval

void CheckInterrupt(void)
{
    if(taskVar_mode == -1)
    {
        Serial.println("     Service Mode Activated    ");
        taskVar_mode = 0;    
    }
    if(taskVar_mode == 0)
    {   
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW) || (ReadInput(INPUT_RST) == LOW))
        {
            currentMillis[0] = millis();
            if (currentMillis[0] - previousMillis[0] >= interval) 
            {
                previousMillis[0] = currentMillis[0];
                if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
                {
                    Serial.println("   Maintenance Mode Activated  ");
                    while((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW));
                    taskVar_mode = 1;
                }
                if((ReadInput(INPUT_RST) == LOW) && (taskVar_mode == 0))
                {
                    Serial.println("       Reset Mode Activated    ");
                    taskVar_mode = 2;
                }
            }
        }
        else
        {
            previousMillis[0] = millis();
        }
        
    }
    if(taskVar_mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            currentMillis[1] = millis();
            if (currentMillis[1] - previousMillis[1] >= interval) 
            {
                previousMillis[1] = currentMillis[1];
                if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
                {
                    Serial.println("     Service Mode Activated    ");
                    while((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW));
                    taskVar_mode = 0;
                }
            }
        }
        else
        {
            previousMillis[1] = millis();
        }
    }
}

void LiftOperation(void)
{
    // Manual Mode
    if(taskVar_mode == 1)   
    {
        if(((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW)) || ((ReadInput(INPUT_BUP) == HIGH) && (ReadInput(INPUT_BDN) == HIGH)))
        {
            digitalWrite(OUTPUT2_UPM, LOW);
            digitalWrite(OUTPUT2_DNM, LOW);
        }
        else
        {
            if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
            {
                delay(100);
                if(ReadInput(INPUT_BUP) == LOW)
                {
                    digitalWrite(OUTPUT2_UPM, !ReadInput(INPUT_BUP));
                }
                if(ReadInput(INPUT_BDN) == LOW)
                {
                    digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_BDN));
                }
            }
        }
    }
    // Reset Mode
    if(taskVar_mode == 2)   
    {
        do
        {
            digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_FL0));
        } while(ReadInput(INPUT_FL0) == LOW);
        Serial.println("     Service Mode Activated    ");
        taskVar_mode = 1;
    }    
}

