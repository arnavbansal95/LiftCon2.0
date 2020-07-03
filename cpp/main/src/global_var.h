#include "Arduino.h"

#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

typedef enum
{
    SERVICE,
    MAINTENANCE,
    RESET,
    STARTUP,
    BREAKDOWN
} mode_t;

typedef enum
{
    UP,
    DOWN,
    IDLE, 
    HALT
} motion_t;

typedef struct
{
    uint8_t ESP;
    uint8_t GRL;
    uint8_t VSP;
} BreakDown;

void setMode(mode_t* mode);             // Saves the Mode into Global Var
void setMotion(motion_t* motion);       // Saves the Motion into Global Var
void setBkDn(BreakDown BkDn);           // Saves the BreakDown Condition into Global Struct
mode_t getMode(void);                   // Returns the Global Var Mode
motion_t getMotion(void);               // Returns the Global Var Motion
BreakDown getBkDn(void);                // Returns the Global Struct BkDn 

#endif