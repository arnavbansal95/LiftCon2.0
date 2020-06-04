#include "task.h"

bool            taskVar_Critical = false;               // False: System Stop, True: Operational    
mode_t          taskVar_mode = STARTUP;                 // Stores Current state of LiftOperation 
unsigned long   previousMillis[2] = {0, 0};             // will store last time 
unsigned long   currentMillis[2];                       // will store current time
const long      interval = 5000;                        // interval

void CriticalCheck(void)
{
    static uint8_t taskVar_CriticalRes;
    taskVar_CriticalRes = ReadInput(INPUT_GLS) | ReadInput(INPUT_ESP) | ReadInput(INPUT_VSP); 
    if(taskVar_mode == STARTUP)
    {
        if(taskVar_CriticalRes == LOW)
        {
            Serial.println(" Inital Critical Check: Passed ");
            Serial.println("     Service Mode Activated    ");
            taskVar_mode = SERVICE;
            taskVar_Critical = true;
        }
        if(taskVar_CriticalRes == HIGH)
        {
            Serial.println(" Inital Critical Check: Failed ");
            taskVar_Critical = false;
        }
        digitalWrite(OUTPUT2_MCN, !taskVar_CriticalRes);
    }
    else
    {
        if((taskVar_CriticalRes == LOW) && (!taskVar_Critical))
        {
            Serial.println("     Critical Check: Passed    ");
            taskVar_Critical = true;
        }
        if((taskVar_CriticalRes == HIGH) && (taskVar_Critical))
        {
            Serial.println("     Critical Check: Failed    ");
            taskVar_Critical = false;
        }
        digitalWrite(OUTPUT2_MCN, !taskVar_CriticalRes);
    }
}

void CheckInterrupt(void)
{
    if(taskVar_mode == STARTUP)
    {
            
    }
    if(taskVar_mode == SERVICE)
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
                    taskVar_mode = MAINTENANCE;
                }
                if((ReadInput(INPUT_RST) == LOW) && (taskVar_mode == SERVICE))
                {
                    if((ReadInput(INPUT_FL0) == LOW) && (ReadInput(INPUT_FL1) == LOW) && (ReadInput(INPUT_FL2) == LOW) && (ReadInput(INPUT_FL3) == LOW))
                    {
                        Serial.println("       Reset Mode Activated    ");
                        taskVar_mode = RESET;
                    }
                }
            }
        }
        else
        {
            previousMillis[0] = millis();
        }
        
    }
    if(taskVar_mode == MAINTENANCE)
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
                    taskVar_mode = SERVICE;
                }
            }
        }
        else
        {
            previousMillis[1] = millis();
        }
    }
}

bool DoorCheck(void)
{
    static uint8_t taskVar_DoorLimitStatus;
    taskVar_DoorLimitStatus = ReadInput(INPUT_DLS); 
    digitalWrite(OUTPUT2_DIN, taskVar_DoorLimitStatus);
    if(taskVar_DoorLimitStatus == LOW)
    {
        return(true);
    }
    else
    {
        Serial.println("        Door Open: Error       ");
        return(false);
    }
    
}

void LiftOperation(void)
{
    if(taskVar_Critical)
    {
        static bool taskVar_DoorLimitStatus_LFTOP;
        taskVar_DoorLimitStatus_LFTOP = DoorCheck();
        // Maintenance Mode
        if(taskVar_mode == MAINTENANCE)   
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
                        digitalWrite(OUTPUT2_UPM, (!ReadInput(INPUT_BUP) & !ReadInput(INPUT_RLU)));
                    }
                    if(ReadInput(INPUT_BDN) == LOW)
                    {
                        digitalWrite(OUTPUT2_DNM, (!ReadInput(INPUT_BDN) & !ReadInput(INPUT_RLD)));
                    }
                }
            }
        }
        // Reset Mode
        if(taskVar_mode == RESET)   
        {
            if(taskVar_DoorLimitStatus_LFTOP)
            {
                do
                {
                    digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_FL0));
                } while(ReadInput(INPUT_FL0) == LOW);
                digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_FL0));
                Serial.println("     Service Mode Activated    ");
                taskVar_mode = SERVICE;
            }
        }
    }        
}

