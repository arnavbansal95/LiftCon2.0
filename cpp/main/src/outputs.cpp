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
    u8g.begin();
    u8g.setFont(u8g_font_helvB08);
}

void SplashScreen()
{
    u8g.firstPage();  
    do 
    {
        u8g.drawFrame(0, 0, 128, 64);
        u8g.drawFrame(2, 2, 126, 62);
        u8g.drawStr(8, 20, "Lift Controller 2.0");
        u8g.drawStr(8, 35, "Designed in Austria");
        u8g.drawStr(8, 50, "   Made in India   ");     
    } while(u8g.nextPage());
}