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
  runner.init();
  Serial.println("  Scheduler:   Initialized     ");
  runner.addTask(SplashScreenTask);
  Serial.println("      Tasks:   Added           ");
  SplashScreenTask.enable();
  Serial.println("      Tasks:   Enabled         ");
  Serial.println("===============================");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  runner.execute();
   
  /* Serial.println("Writing A");
  SendData("A", MB_2);
  delay(100); */
  
  /* char ch = ReceiveData(MB_2); 
  if(ch != NULL)
  {
    Serial.println(ch);
  } */
}
