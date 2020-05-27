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
  Serial.println(ReadInput(INPUT_DLS));
  Serial.println(ReadInput(INPUT_FL0));
  Serial.println(ReadInput(INPUT_FL1));
  Serial.println(ReadInput(INPUT_FL2));
  Serial.println(ReadInput(INPUT_FL3));
  Serial.println("========");
  delay(1000);
}
