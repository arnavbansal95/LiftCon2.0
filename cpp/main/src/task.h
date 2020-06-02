#include <TaskScheduler.h>
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

static void ManualOperation(void);
static void CheckUPDownManual(void);            // Switch Auto <-> Manual Mode

static Task CheckUPDownManualTask(10, TASK_FOREVER, &CheckUPDownManual);
static Task ManualOperationTask(10, TASK_FOREVER, &ManualOperation);
static Task SplashScreenTask(1, 5000, &SplashScreen);
static Scheduler runner;

#endif