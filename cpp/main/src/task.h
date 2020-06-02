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

void CheckInterrupt(void);
void LiftOperation(void);

static Scheduler runner;
static Task CheckInterruptTask(10, TASK_FOREVER, &CheckInterrupt, &runner, true);
static Task LiftOperationTask(10, TASK_FOREVER, &LiftOperation, &runner, true);
static Task SplashScreenTask(1, 5000, &SplashScreen, &runner, true);

#endif