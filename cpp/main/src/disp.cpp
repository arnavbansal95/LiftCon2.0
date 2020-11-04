#include "disp.h"

void InitLCD(void)
{
    // assign default color value
    u8g.begin();
}

void Display(void)
{
    static int delayVar = 50;
    dispVar_mode = getMode();
    dispVar_motion = getMotion();
    dispVar_BkDn = getBkDn();
    dispVar_Floor = getFloor();
    dispVar_doorStatus = getDoorStatus();
    if(dispVar_mode == STARTUP || dispVar_mode > 10)
    {
        u8g.firstPage();  
        do 
        {
            StartupScreen();
        } while(u8g.nextPage());
        delay(delayVar);
    }   
    if(dispVar_mode == SERVICE)
    {
        u8g.firstPage();  
        do 
        {
            ServiceMode();
        } while(u8g.nextPage());
        delay(delayVar);
    }
    if(dispVar_mode == MAINTENANCE)
    {
        u8g.firstPage();  
        do 
        {
            MaintenanceMode();
        } while(u8g.nextPage());
        delay(delayVar);
    }
    if(dispVar_mode == BREAKDOWN)
    {
        u8g.firstPage();  
        do 
        {
            BreakdownMode();
        } while(u8g.nextPage());
        delay(delayVar);
    }
    if(dispVar_mode == RESET)
    {
        u8g.firstPage();  
        do 
        {
            ResetMode();
        } while(u8g.nextPage());
        delay(delayVar);
    }
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
    if((dir == IDLE) && (getDoorStatus()))
    {
        u8g.setFont(u8g_font_helvB24);
        u8g.drawStr(94, 50, "--");
        u8g.drawCircle(104, 40, 16);
        u8g.drawCircle(104, 40, 15);
    }
    if((dir == HALT) || (!getDoorStatus()))
    {
        u8g.setFont(u8g_font_helvB24);
        u8g.drawStr(99, 53, "!");
        u8g.drawCircle(104, 40, 16);
        u8g.drawCircle(104, 40, 15); 
    }

}

void StartupScreen(void)
{
    #if DEMO_MODE == 1
        BasicFrame();
        u8g.setFont(u8g_font_helvB10);
        u8g.drawStr(15, 15, " Demo Mode     ");
        Motion(HALT);
        u8g.setFont(u8g_font_04b_03);
        u8g.drawStr(4, 32, "Warning: This is");
        u8g.drawStr(4, 44, " Demonstration");
        u8g.drawStr(4, 56, " Purposes only!");
    #else
        BasicFrameNoLine();
        u8g.setFont(u8g_font_helvB10);
        u8g.drawStr(4, 15, "Lift Controller 2.0");
        u8g.setFont(u8g_font_courR08);
        u8g.drawStr(4, 32, "For Assistance:");
        u8g.drawStr(4, 44, "Sharad Bansal");
        u8g.drawStr(4, 56, "+91-9958586960");
    #endif
}

void ServiceMode(void)
{
    static char ch[18];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(15, 15, "      Service      ");
    Motion(dispVar_motion);
    u8g.setFont(u8g_font_04b_03);
    if(dispVar_Floor.CF != -1)
    {
        strcpy(ch, "Floor Status: --");
        if(dispVar_Floor.CF < 10)
        {
            ch[14] = '0';
            ch[15] = (dispVar_Floor.CF) + '0';
        }
        else
        {
            ch[14] = ((dispVar_Floor.CF % 100) / 10) + '0';
            ch[15] = (dispVar_Floor.CF % 10) + '0';
        }
        u8g.drawStr(4, 32, ch);
    }
    if(dispVar_Floor.CF == -1)
    {
        strcpy(ch, "Floor Status: --");
        u8g.drawStr(4, 32, ch);    
    }
    if(dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: OK");
        u8g.drawStr(4, 44, ch);
    }
    if(!dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: FLT");
        u8g.drawStr(4, 44, ch);
    }
    if(dispVar_Floor.TF != -1)
    {
        strcpy(ch, "Target Floor: --");
        if(dispVar_Floor.TF < 10)
        {
            ch[14] = '0';
            ch[15] = (dispVar_Floor.TF) + '0';
        }
        else
        {
            ch[14] = ((dispVar_Floor.TF % 100) / 10) + '0';
            ch[15] = (dispVar_Floor.TF % 10) + '0';
        }
        u8g.drawStr(4, 56, ch);
    }
    if(dispVar_Floor.TF == -1)
    {
        strcpy(ch, "Target Floor: --");
        u8g.drawStr(4, 56, ch);
    }
}

void MaintenanceMode(void)
{
    static char ch[18];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(5, 15, "    Maintenance    ");
    Motion(dispVar_motion);
    u8g.setFont(u8g_font_04b_03);
    if(dispVar_Floor.CF != -1)
    {
        strcpy(ch, "Floor Status: --");
        if(dispVar_Floor.CF < 10)
        {
            ch[14] = '0';
            ch[15] = (dispVar_Floor.CF) + '0';
        }
        else
        {
            ch[14] = ((dispVar_Floor.CF % 100) / 10) + '0';
            ch[15] = (dispVar_Floor.CF % 10) + '0';
        }
        u8g.drawStr(4, 32, ch);
    }
    if(dispVar_Floor.CF == -1)
    {
        strcpy(ch, "Floor Status: --");
        u8g.drawStr(4, 32, ch);    
    }
    if (dispVar_motion == UP)
    {   
        strcpy(ch, "Drive Motion: UP");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == DOWN)
    {
        strcpy(ch, "Drive Motion: DN");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == IDLE)
    {
        strcpy(ch, "Drive Motion: --");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == HALT)
    {
        strcpy(ch, "Drive Motion: --");
        u8g.drawStr(4, 44, ch);
    }
    if(dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: OK");
        u8g.drawStr(4, 56, ch);
    }
    if(!dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: FLT");
        u8g.drawStr(4, 56, ch);
    }
}

void ResetMode(void)
{
    static char ch[18];
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(7, 15, "         Reset  ");
    Motion(dispVar_motion);
    u8g.setFont(u8g_font_04b_03);
    if(dispVar_Floor.CF != -1)
    {
        strcpy(ch, "Floor Status: --");
        if(dispVar_Floor.CF < 10)
        {
            ch[14] = '0';
            ch[15] = (dispVar_Floor.CF) + '0';
        }
        else
        {
            ch[14] = ((dispVar_Floor.CF % 100) / 10) + '0';
            ch[15] = (dispVar_Floor.CF % 10) + '0';
        }
        u8g.drawStr(4, 32, ch);
    }
    if(dispVar_Floor.CF == -1)
    {
        strcpy(ch, "Floor Status: --");
        u8g.drawStr(4, 32, ch);    
    }
    if (dispVar_motion == UP)
    {   
        strcpy(ch, "Drive Motion: UP");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == DOWN)
    {
        strcpy(ch, "Drive Motion: DN");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == IDLE)
    {
        strcpy(ch, "Drive Motion: --");
        u8g.drawStr(4, 44, ch);
    }
    if (dispVar_motion == HALT)
    {
        strcpy(ch, "Drive Motion: --");
        u8g.drawStr(4, 44, ch);
    }
    if(dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: OK");
        u8g.drawStr(4, 56, ch);
    }
    if(!dispVar_doorStatus)
    {
        strcpy(ch, "Door Status: FLT");
        u8g.drawStr(4, 56, ch);
    }
}

void BreakdownMode(void)
{
    int x = 28;
    static char ch[18];
    static BreakDown dispVar_BkDnVar;
    dispVar_BkDnVar = getBkDn();
    BasicFrame();
    u8g.setFont(u8g_font_helvB10);
    u8g.drawStr(5, 15, "     Breakdown     ");
    Motion(HALT);
    u8g.setFont(u8g_font_5x8);
    if(dispVar_BkDnVar.ESP == LOW)
    {
        strcpy(ch, "ESP: OK");
        u8g.drawStr(4, 32, ch);
    }
    if(dispVar_BkDnVar.ESP == HIGH)
    {
        strcpy(ch, "ESP: FLT");
        u8g.drawStr(4, 32, ch);
    }
    if(dispVar_BkDnVar.GRL == LOW)
    {
        strcpy(ch, "GRL: OK");
        u8g.drawStr(4, 44, ch);
    }
    if(dispVar_BkDnVar.GRL == HIGH)
    {
        strcpy(ch, "GRL: FLT");
        u8g.drawStr(4, 44, ch);
    }
    if(dispVar_BkDnVar.VSP == LOW)
    {
        strcpy(ch, "VSP: OK");
        u8g.drawStr(4, 56, ch);
    }
    if(dispVar_BkDnVar.VSP == HIGH)
    {
        strcpy(ch, "VSP: FLT");
        u8g.drawStr(4, 56, ch);
    }
}