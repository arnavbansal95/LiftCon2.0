// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "TaskScheduler.h"
#include "src/task.h"

static unsigned long   main_previousMillis = 0; 
static unsigned long   main_currentMillis; 

void setup() 
{
  // put your setup code here, to run once:
  InitLCD();
  InitComms();
  InitInputs();
  InitOutputs();
  InitTime();
  
  main_currentMillis = millis();
  while(main_currentMillis - main_previousMillis <= 10000)
  {
    Display();
    main_currentMillis = millis();
  }
  
  Serial.println("===============================");
  Serial.println("     Lift Controller V2.0      ");
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
