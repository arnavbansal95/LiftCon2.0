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
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(digitalRead(INPUT_SP1) == LOW)
  {
    digitalWrite(OUTPUT2_SP1, HIGH);
    digitalWrite(OUTPUT2_SP2, LOW);
    digitalWrite(OUTPUT2_DIN, LOW);
    digitalWrite(OUTPUT2_DNM, LOW);
    digitalWrite(OUTPUT2_UPM, LOW);
    digitalWrite(OUTPUT2_MCN, HIGH);
  }
  if(digitalRead(INPUT_ESP) == LOW)
  {
    digitalWrite(OUTPUT2_SP1, LOW);
    digitalWrite(OUTPUT2_SP2, HIGH);
    digitalWrite(OUTPUT2_DIN, LOW);
    digitalWrite(OUTPUT2_DNM, LOW);
    digitalWrite(OUTPUT2_UPM, HIGH);
    digitalWrite(OUTPUT2_MCN, LOW);
  }
  if(digitalRead(INPUT_RST) == LOW)
  {
    digitalWrite(OUTPUT2_SP1, LOW);
    digitalWrite(OUTPUT2_SP2, LOW);
    digitalWrite(OUTPUT2_DIN, HIGH);
    digitalWrite(OUTPUT2_DNM, HIGH);
    digitalWrite(OUTPUT2_UPM, LOW);
    digitalWrite(OUTPUT2_MCN, LOW);
  }
  if(digitalRead(INPUT_OLR) == LOW)
  {
    digitalWrite(OUTPUT2_SP1, HIGH);
    digitalWrite(OUTPUT2_SP2, HIGH);
    digitalWrite(OUTPUT2_DIN, HIGH);
    digitalWrite(OUTPUT2_DNM, HIGH);
    digitalWrite(OUTPUT2_UPM, HIGH);
    digitalWrite(OUTPUT2_MCN, HIGH);
  }
}
