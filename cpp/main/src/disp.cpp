#include "disp.h"

void InitLCD(void)
{
    // assign default color value
    u8g.begin();
}

void Display(void)
{
    // static uint8_t x = 1;
    u8g.firstPage();  
    do 
    {
        if(globalVar_mode == STARTUP)
        {
            StartupScreen();
            delay(5000);
        }   
        if(globalVar_mode == SERVICE)
        {
            ServiceMode();
        }
        if(globalVar_mode == MAINTENANCE)
        {
            MaintenanceMode();
        }
    } while(u8g.nextPage());
}

void BasicFrameNoLine(void)
{
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawFrame(1, 1, 126, 62);
    u8g.drawFrame(1, 1, 126, 19);
    u8g.drawFrame(1, 1, 126, 18);
}

void BasicFrame(void)
{
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawFrame(1, 1, 126, 62);
    u8g.drawFrame(1, 1, 126, 19);
    u8g.drawFrame(1, 1, 126, 18);
    u8g.drawFrame(80, 19, 48, 64);
    u8g.drawFrame(81, 19, 48, 64);
}

void Motion(motion_t dir)
{
    if(dir == UP)
    {
        u8g.drawTriangle(104,25, 86,56, 122,56);    // UP
    }
    if(dir == DOWN)
    {
        u8g.drawTriangle(122,25, 86,25, 104,56);    // DOWN
    }
    if(dir == IDLE)
    {
        u8g.setFont(u8g_font_helvB24);
        u8g.drawStr(94, 50, "--");
        u8g.drawCircle(104, 40, 16);
        u8g.drawCircle(104, 40, 15);
    }   
}

void StartupScreen(void)
{
    BasicFrameNoLine();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(4, 15, "Lift Controller 2.0");
    u8g.setFont(u8g_font_courR08);
    u8g.drawStr(4, 32, "For Assistance:");
    u8g.drawStr(4, 44, "Sharad Bansal");
    u8g.drawStr(4, 56, "+91-9958586960");
}

void ServiceMode(void)
{
    static char ch[16];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(15, 15, "      Service      ");
    u8g.setFont(u8g_font_04b_03);
    strcpy(ch, "Floor Status: 00");
    u8g.drawStr(4, 32, ch);
    strcpy(ch, "Drive Motion: UP");
    Motion(globalVar_motion);
    u8g.drawStr(4, 44, ch);
    strcpy(ch, "Target Floor: 04");
    u8g.drawStr(4, 56, ch);
}

void MaintenanceMode(void)
{
    static char ch[16];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(5, 15, "    Maintenance    ");
    u8g.setFont(u8g_font_04b_03);
    strcpy(ch, "Floor Status: --");
    u8g.drawStr(4, 32, ch);
    strcpy(ch, "Drive Motion: DN");
    Motion(globalVar_motion);
    u8g.drawStr(4, 44, ch);
    strcpy(ch, "Target Floor: --");
    u8g.drawStr(4, 56, ch);
}

void BreakdownMode(void)
{
    static char ch[16];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(5, 15, "     Breakdown     ");
    u8g.setFont(u8g_font_helvB24);
    u8g.drawStr(99, 53, "!");
    u8g.drawCircle(104, 40, 16);
    u8g.drawCircle(104, 40, 15); 
    u8g.setFont(u8g_font_5x8);
    strcpy(ch, "ESP: OK");
    u8g.drawStr(4, 32, ch);
    strcpy(ch, "GRL: FAULT");
    u8g.drawStr(4, 44, ch);
    strcpy(ch, "VSP: OK");
    u8g.drawStr(4, 56, ch);
}