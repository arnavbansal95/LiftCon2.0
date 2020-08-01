#include "Arduino.h"
#include "EEPROM.h"
#include "global_var.h"

#ifndef TIME_H_
#define TIME_H_

#define HOURS_EEPROM_RES    0
#define DAYS_EEPROM_RES     1

static unsigned long   startMillis;
static unsigned long   elapsedSeconds;
static uint8_t         elapsedMins;
static uint8_t         elapsedHours;
static uint8_t         elapsedDays;

void InitTime(void);            // Initialize Time
void SetTime(void);             // Up Time
void WriteTime(void);           // Write Time in EEPROM
void GetTime(void);             // Get Time from EEPROM
void ShutDown(mode_t* mode);    // Set Shutdown Signal

#endif