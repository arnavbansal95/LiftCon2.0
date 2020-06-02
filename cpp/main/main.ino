// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "TaskScheduler.h"
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
  runner.startNow();
  Serial.println("  Scheduler:   Initialized     ");
  Serial.println("===============================");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  runner.execute();
}
