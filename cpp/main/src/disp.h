#include "Arduino.h"
#include "lib/U8glib/src/U8glib.h"
#include "global_var.h"

#ifndef DISP_H_
#define DISP_H_

// LCD Control Pins
#define GR_LCD_RS  53
#define GR_LCD_RW  51
#define GR_LCD_E   52
static U8GLIB_ST7920_128X64_1X u8g(GR_LCD_E, GR_LCD_RW, GR_LCD_RS);

void InitLCD(void);                             // Initialize LCD
void Display(void);                             // Main Display Function 
void BasicFrame(void);                          // Line Frame
void BasicFrameNoLine(void);                    // Line Frame, No Separator
void Motion(motion_t dir);                      // Motion Function
void ServiceMode(void);                         // Service Mode Loop
void MaintenanceMode(void);                     // Maintenance Mode Loop
void BreakdownMode(void);                       // Breakdown Mode Loop
void StartupScreen(void);                       // Startup Screen Loop

#endif