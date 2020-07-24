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

void OutputMotion(motion_t smVar = HALT)
{
    if((smVar == HALT) || (smVar == IDLE))
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, LOW);
    }
    if(smVar == UP)
    {
        digitalWrite(OUTPUT2_DNM, LOW);
        digitalWrite(OUTPUT2_UPM, (!ReadInput(INPUT_BUP) & !ReadInput(INPUT_RLU)));
    }
    if(smVar == DOWN)
    {
        digitalWrite(OUTPUT2_UPM, LOW);
        digitalWrite(OUTPUT2_DNM, (!ReadInput(INPUT_BDN) & !ReadInput(INPUT_RLD)));
    }
}