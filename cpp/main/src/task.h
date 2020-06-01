#include <TaskScheduler.h>
#include "outputs.h"
#include "inputs.h"
#include "comms.h"

#ifndef TASK_H_
#define TASK_H_

static Task SplashScreenTask(1, 5000, &SplashScreen);
static Scheduler runner;

#endif