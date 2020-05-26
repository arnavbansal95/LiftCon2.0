#include "outputs.h"

void InitOutputs()
{
    for(int i=2;i<14;i++)
    {
        pinMode(i, OUTPUT);
    }
    for(int i=23;i<34;i=i+2)
    {
        pinMode(i, OUTPUT);
    }
}