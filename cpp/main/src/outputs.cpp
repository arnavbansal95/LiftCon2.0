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
    // assign default color value
    if(LCD.getMode() == U8G_MODE_R3G3B2) 
    {
        LCD.setColorIndex(255);     // white
    }
    else if(LCD.getMode() == U8G_MODE_GRAY2BIT) 
    {
        LCD.setColorIndex(3);         // max intensity
    }
    else if(LCD.getMode() == U8G_MODE_BW) 
    {
        LCD.setColorIndex(1);         // pixel on
    }
    else if(LCD.getMode() == U8G_MODE_HICOLOR) 
    {
        LCD.setHiColorByRGB(255,255,255);
    }
    LCD.setFont(u8g_font_unifont);
    LCD.drawStr( 0, 22, "ARNAV BANSAL");
}