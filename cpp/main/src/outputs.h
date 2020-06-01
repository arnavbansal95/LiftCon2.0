#include "Arduino.h"
#include "lib/LCDLib/src/U8glib.h"

#ifndef OUTPUTS_H_
#define OUTPUTS_H_

// 24v Isolated Signal Outputs
#define OUTPUT1_1  13
#define OUTPUT1_2  12
#define OUTPUT1_3  11
#define OUTPUT1_4  10
#define OUTPUT1_5   9
#define OUTPUT1_6   8
#define OUTPUT1_7   7
#define OUTPUT1_8   6
#define OUTPUT1_9   5
#define OUTPUT1_10  4
#define OUTPUT1_11  3
#define OUTPUT1_12  2

// Relay Outputs
#define OUTPUT2_SP1  23     // Spare 1 Relay 
#define OUTPUT2_SP2  25     // Spare 2 Relay
#define OUTPUT2_DIN  27     // Door Indicator  
#define OUTPUT2_DNM  29     // Down Motion
#define OUTPUT2_UPM  31     // Up Motion
#define OUTPUT2_MCN  33     // Main Contactor

// LCD Control Pins
#define GR_LCD_RS  53
#define GR_LCD_RW  51
#define GR_LCD_E   52
static U8GLIB_ST7920_128X64 LCD(GR_LCD_E, GR_LCD_RW, GR_LCD_RS, U8G_PIN_NONE);

void InitOutputs(void);              // Initialize Outputs
void InitLCD(void);                  // Initialize LCD

#endif