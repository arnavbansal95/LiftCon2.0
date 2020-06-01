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
    if(u8g.getMode() == U8G_MODE_R3G3B2) 
    {
        u8g.setColorIndex(255);     // white
    }
    else if(u8g.getMode() == U8G_MODE_GRAY2BIT) 
    {
        u8g.setColorIndex(3);         // max intensity
    }
    else if(u8g.getMode() == U8G_MODE_BW) 
    {
        u8g.setColorIndex(1);         // pixel on
    }
    else if(u8g.getMode() == U8G_MODE_HICOLOR) 
    {
        u8g.setHiColorByRGB(255,255,255);
    }
    u8g.setFont(u8g_font_6x10);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
    u8g.drawStr( 0, 22, "ARNAV BANSAL");
}