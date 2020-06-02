#include "TaskSchedulerDeclarations.h"
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

void CheckUPDownManual(void);
void ManualOperation(void);
void AutoOperation(void);

static Scheduler runner;
static Task CheckUPDownManualTask(10, TASK_FOREVER, &CheckUPDownManual, &runner, true);
static Task ManualOperationTask(500, TASK_FOREVER, &ManualOperation, &runner, true);
static Task SplashScreenTask(1, 5000, &SplashScreen, &runner, true);

#endif