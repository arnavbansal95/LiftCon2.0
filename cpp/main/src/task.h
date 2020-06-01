#include "src/outputs.h"
#include "src/inputs.h"
#include "src/comms.h"
#include "lib/TaskScheduler/src/TaskScheduler.h"

#ifndef TASK_H_
#define TASK_H_

void InitSystem(void);

static Task SplashScreenTask(1, 5000, &SplashScreen);
static Scheduler runner;

#endif