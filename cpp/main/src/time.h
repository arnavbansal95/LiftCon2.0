#include "Arduino.h"
#include "EEPROM.h"
#include "global_var.h"

#ifndef TIME_H_
#define TIME_H_

#define DAYS_EEPROM_RES     0
#define DAYS2_EEPROM_RES    1
#define HOURS_EEPROM_RES    2
#define MINS_EEPROM_RES     3
#define SECONDS_EEPROM_RES  4



static unsigned long    startMillis;            // Variable to save CurrentMillis of execution
static unsigned long    elapsedSeconds;         // Variable to save Seconds of execution
static uint8_t          elapsedMins;            // Variable to save Mins of execution
static uint8_t          elapsedHours;           // Variable to save hours of execution
                                                // total days = (days-2) * 255 + days-1 (Overflow - about 178 years) 
static uint8_t          elapsedDays;            // Variable to save days-1 of execution
static uint8_t          elapsedDays2;           // Variable to save days-2 of execution
static uint8_t          elapsedDaysCalc;        // Variable used for days calculation
static uint8_t          writeInterlock = 0;     // Variable to prevent multiple writes WRITE = 0, HOLD = 1
static uint16_t         elapsedDaysDisp;        // Variable used for days calculation display only

void InitTime(void);                                // Initialize Time
void SetTime(void);                                 // Up Time
void WriteTime(void);                               // Write Time in EEPROM
void GetTime(void);                                 // Get Time from EEPROM
void CheckShutDown(mode_t* mode);                   // Set Shutdown Signal
void ResetTime(void);                               // Reset Time in EEPROM
#endif