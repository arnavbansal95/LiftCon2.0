#include "TaskSchedulerDeclarations.h"
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

void CheckUPDownManual(void);

static Task CheckUPDownManualTask(10, TASK_FOREVER, &CheckUPDownManual);
static Task SplashScreenTask(1, 5000, &SplashScreen);
static Scheduler runner;

#endif