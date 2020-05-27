// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "src/outputs.h"
#include "src/inputs.h"

void setup() 
{
  // put your setup code here, to run once:
  InitInputs();
  InitOutputs();
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  ReadInput(INPUT_DLS);
  ReadInput(INPUT_FL0);
  delay(1000);
}
