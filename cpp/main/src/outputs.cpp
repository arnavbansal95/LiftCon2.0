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

void InitLCD()
{
    LCD.setFont(u8g_font_unifont);
    LCD.setColorIndex(1); // Instructs the display to draw with a pixel on.
    LCD.drawStr( 0, 20, "ARNAV BANSAL");
}