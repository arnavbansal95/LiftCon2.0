#include "TaskSchedulerDeclarations.h"
#include "outputs.h"
#include "inputs.h"
#include "comms.h"
#include "disp.h"
#include "global_var.h"
#include "time.h"

#ifndef TASK_H_
#define TASK_H_

typedef enum
{
    WAITING,
    READY,
    RUNNING
} motor_t;

void CheckInterrupt(void);      // Checks Operation Conditions
bool CriticalCheck(void);       // Checks Gravity Limit, Emergency Stop, VSP_D2 
bool DoorCheck(void);           // Checks Door Status
int  GetTargetFloor(void);      // Returns Target Floor
int  GetCurrentFloor(void);     // Returns Current Floor Status
void LiftOperation(void);       // Performs Operation 


static Scheduler runner;
static Task CriticalCheckTask(1, TASK_FOREVER, &CriticalCheck, &runner, true);
static Task CheckInterruptTask(10, TASK_FOREVER, &CheckInterrupt, &runner, true);
static Task DisplayTask(10, TASK_FOREVER, &Display, &runner, true);
static Task LiftOperationTask(10, TASK_FOREVER, &LiftOperation, &runner, true);

#endif