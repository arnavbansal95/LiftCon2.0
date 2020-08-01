#include "outputs.h"

void InitOutputs()
{
    for(int i=2;i<14;i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    for(int i=23;i<34;i=i+2)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}

void OutputMotion(motion_t smVar = HALT, mode_t mdVar = STARTUP)
{
    if((smVar == HALT) || (smVar == IDLE))
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, LOW);
    }
    if((smVar == UP) && (mdVar == MAINTENANCE))
    {
        digitalWrite(OUTPUT2_DNM, LOW);
        digitalWrite(OUTPUT2_UPM, (!ReadInput(INPUT_BUP) & !ReadInput(INPUT_RLU)));
    }
    if((smVar == DOWN) && (mdVar == MAINTENANCE))
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, (!ReadInput(INPUT_BDN) & !ReadInput(INPUT_RLD)));
    }
    if((smVar == DOWN) && (mdVar == RESET))
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, (!ReadInput(INPUT_FL0) & !ReadInput(INPUT_RLD)));
    }
    if((smVar == UP) && (mdVar == SERVICE))
    {
        digitalWrite(OUTPUT2_DNM, LOW);
        digitalWrite(OUTPUT2_UPM, !ReadInput(INPUT_RLU));
    }
    if((smVar == DOWN) && (mdVar == SERVICE))
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_RLD));
    }
}