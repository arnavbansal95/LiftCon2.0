// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "TaskScheduler.h"
#include "src/task.h"

int taskVar_mode = 0;        // mode = 0: Auto Mode, mode = 1: Manual Mode

static void CheckUPDownManual(void)
{
    if(taskVar_mode == 0)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
            {
                taskVar_mode = 1;
                Serial.println("Manual Mode Activated");
                delay(1000);
            }
        }
    }
    if(taskVar_mode == 1)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            delay(5000);
            if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
            {
                taskVar_mode = 0;
                Serial.println("Auto Mode Activated");
                delay(1000);
            }
        }
    }
}

Task CheckUPDownManualTask(10, TASK_FOREVER, &CheckUPDownManual);
Task SplashScreenTask(1, 5000, &SplashScreen);
Scheduler runner;

void setup() 
{
  // put your setup code here, to run once:
  InitComms();
  InitInputs();
  InitOutputs();
  InitLCD();
  Serial.println("===============================");
  Serial.println("     System:   Initialized     ");
  runner.init();
  Serial.println("  Scheduler:   Initialized     ");
  runner.addTask(SplashScreenTask);
  runner.addTask(CheckUPDownManualTask);
  Serial.println("      Tasks:   Added           ");
  SplashScreenTask.enable();
  CheckUPDownManualTask.enable();
  Serial.println("      Tasks:   Enabled         ");
  Serial.println("===============================");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  runner.execute();
}
