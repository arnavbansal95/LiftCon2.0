#include "inputs.h"

void InitInputs()
{
    pinMode(INPUT_BDN, INPUT);
    pinMode(INPUT_BUP, INPUT);
    pinMode(INPUT_DLS, INPUT);
    pinMode(INPUT_ESP, INPUT);
    pinMode(INPUT_FL0, INPUT);
    pinMode(INPUT_FL1, INPUT);
    pinMode(INPUT_FL2, INPUT);
    pinMode(INPUT_FL3, INPUT);
    pinMode(INPUT_FL4, INPUT);
    pinMode(INPUT_FL5, INPUT);
    pinMode(INPUT_FP0, INPUT);
    pinMode(INPUT_FP1, INPUT);
    pinMode(INPUT_FP2, INPUT);
    pinMode(INPUT_FP3, INPUT);
    pinMode(INPUT_FP4, INPUT);
    pinMode(INPUT_FP5, INPUT);
    pinMode(INPUT_GLS, INPUT);
    pinMode(INPUT_OLR, INPUT);
    pinMode(INPUT_RLD, INPUT);
    pinMode(INPUT_RLU, INPUT);
    pinMode(INPUT_RST, INPUT);
    pinMode(INPUT_SP1, INPUT);
    pinMode(INPUT_VSP, INPUT);
}

uint8_t ReadInput(int Input)
{
    uint8_t ret = 0;
    if(Input <= 53)
    {
        ret = digitalRead(Input);
    }
    if((Input >= 54) && (Input <= 69))
    {
        ret = analogRead(Input);
    } 
    return ret;
}