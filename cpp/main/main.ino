// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "src/outputs.h"
#include "src/inputs.h"
#include "src/comms.h"

void setup() 
{
  // put your setup code here, to run once:
  InitComms();
  InitInputs();
  InitOutputs();
  }

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.println("Writing A");
  SendData("A", MB1);
  delay(100);
}
