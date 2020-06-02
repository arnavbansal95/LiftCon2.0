// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "src/task.h"

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
