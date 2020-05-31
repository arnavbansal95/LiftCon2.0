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
  for(int i=54;i<70;i++)
  {
    if(ReadInput(i) == LOW)
    {
      Serial.println(i);
      if((i < 65) && (i % 2 != 0))
      {
        digitalWrite(i-31, HIGH);
      }
      delay(200);
    }
  } 
  for(int i=37;i<50;i+=2)
  {
    if(ReadInput(i) == LOW)
    {
      Serial.println(i);
      delay(200);
    }
  }
}
