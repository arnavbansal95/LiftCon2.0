// Lift Control Code
// Version 2.0
// Developed by - Arnav Bansal

#include "U8glib.h"
#include "src/outputs.h"
#include "src/inputs.h"
#include "src/comms.h"

void setup() 
{
  // put your setup code here, to run once:
  InitComms();
  InitInputs();
  InitOutputs();
  InitLCD();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  /* Serial.println("Writing A");
  SendData("A", MB_2);
  delay(100); */
  
  char ch = ReceiveData(MB_2); 
  if(ch != NULL)
  {
    Serial.println(ch);
  }
}
