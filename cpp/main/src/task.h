#include "TaskSchedulerDeclarations.h"
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

void CheckUPDownManual(void);
void ManualOperation(void);
void AutoOperation(void);

static Task CheckUPDownManualTask(10, TASK_FOREVER, &CheckUPDownManual);
static Task ManualOperationTask(10, TASK_FOREVER, &ManualOperation);
static Task SplashScreenTask(1, 5000, &SplashScreen);
static Scheduler runner;

#endif