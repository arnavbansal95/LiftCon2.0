#include "task.h"

void InitSystem()
{
    InitComms();
    InitInputs();
    InitOutputs();
    InitLCD();
    Serial.println("===============================");
    runner.init();
    Serial.println("  Scheduler:   Initialized     ");
    runner.addTask(SplashScreenTask);
    Serial.println("      Tasks:   Added           ");
    SplashScreenTask.enable();
    Serial.println("      Tasks:   Enabled         ");
    Serial.println("===============================");
}