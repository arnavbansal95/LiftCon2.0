#include "task.h"

int taskVar_mode = 0;        // mode = 0: Auto Mode, mode = 1: Manual Mode

void CheckUPDownManual(void)
{
    if(taskVar_mode == 0)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
            {
                taskVar_mode = 1;
                Serial.println("Manual Mode Activated");
                runner.addTask(ManualOperationTask);
                ManualOperationTask.enable();
                Serial.println("Manual Mode Task Added and Enabled");
                delay(2000);
            }
        }
    }
    if(taskVar_mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
            {
                taskVar_mode = 0;
                Serial.println("Auto Mode Activated");
                ManualOperationTask.disable();
                runner.deleteTask(ManualOperationTask);
                Serial.println("Manual Mode Task Disabled and Deleted");
                delay(2000);
            }
        }
    }
}

void ManualOperation(void)
{
    Serial.println("Manual Mode");
    if(taskVar_mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            digitalWrite(OUTPUT2_UPM, LOW);
            digitalWrite(OUTPUT2_DNM, LOW);
        }
        else
        {
            Serial.println("Manual Mode Loop");
            digitalWrite(OUTPUT2_UPM, !ReadInput(INPUT_BUP));
            digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_BDN));
        }
        
    }
}

