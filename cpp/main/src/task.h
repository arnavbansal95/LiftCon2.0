#include "TaskSchedulerDeclarations.h"
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

typedef enum
{
    SERVICE,
    MAINTENANCE,
    RESET,
    STARTUP
} mode_t;

void CheckInterrupt(void);  // Checks Operation Conditions
void CriticalCheck(void);   // Checks Gravity Limit, Emergency Stop, VSP_D2 
bool DoorCheck(void);       // Checks Door Status
void LiftOperation(void);   // Performs Operation 

static Scheduler runner;
static Task CriticalCheckTask(1, TASK_FOREVER, &CriticalCheck, &runner, true);
static Task CheckInterruptTask(10, TASK_FOREVER, &CheckInterrupt, &runner, true);
static Task LiftOperationTask(10, TASK_FOREVER, &LiftOperation, &runner, true);
static Task SplashScreenTask(1, 5000, &SplashScreen, &runner, true);

#endif