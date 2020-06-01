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
    u8g.setFont(u8g_font_unifont);
}

void SplashScreen()
{
    u8g.firstPage();  
    do 
    {
        u8g.drawStr(0, 22, "ARNAV BANSAL");    
    } while(u8g.nextPage());
}