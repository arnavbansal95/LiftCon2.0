#include "task.h"

int mode = 0;        // mode = 0: Auto Mode, mode = 1: Manual Mode

static void CheckUPDownManual(void)
{
    if(mode == 0)
    {
        if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
            {
                mode = 1;
                Serial.println("Manual Mode Activated");
            }
        }
    }
    if(mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
            {
                mode = 0;
                Serial.println("Auto Mode Activated");
            }
        }
    }
}