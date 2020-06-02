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
                while((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW));
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
                while((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW));
            }
        }
    }
}

void ManualOperation(void)
{
    if(taskVar_mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            digitalWrite(OUTPUT2_UPM, LOW);
            digitalWrite(OUTPUT2_DNM, LOW);
        }
        else
        {
            digitalWrite(OUTPUT2_UPM, !ReadInput(INPUT_BUP));
            digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_BDN));
        }
        
    }
}

