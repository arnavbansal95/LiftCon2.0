#include "Arduino.h"

#ifndef INPUTS_H_
#define INPUTS_H_

#define DEFAULT     128     // Default Value for ReadInput

// Analong Input (To be made into Digital Output)
#define INPUT_DLS   A0      // Door Limit Switch
#define INPUT_FL0   A1      // Floor Limit Switch 0
#define INPUT_FL1   A2      // Floor Limit Switch 1
#define INPUT_FL2   A3      // Floor Limit Switch 2
#define INPUT_FL3   A4      // Floor Limit Switch 3
#define INPUT_FL4   A5      // Floor Limit Switch 4
#define INPUT_FL5   A6      // Floor Limit Switch 5
#define INPUT_RLU   A7      // Rotary Limit UP
#define INPUT_RLD   A8      // Rotary Limit DOWN
#define INPUT_GLS   A9      // Gravity Limit Switch
#define INPUT_FP0   A10     // Floor Push Button 0
#define INPUT_FP1   A11     // Floor Push Button 1
#define INPUT_FP2   A12     // Floor Push Button 2
#define INPUT_FP3   A13     // Floor Push Button 3
#define INPUT_FP4   A14     // Floor Push Button 4
#define INPUT_FP5   A15     // Floor Push Button 5

// Digital Input 
#define INPUT_VSP  49       // VSP D2    
#define INPUT_BUP  47       // UP Push Button
#define INPUT_BDN  45       // DOWN Push Button
#define INPUT_OLR  43       // Overload Relay Input
#define INPUT_RST  41       // Reset Push Button
#define INPUT_ESP  39       // Emergency Stop Switch
#define INPUT_SP1  37       // Spare Input 1

void InitInputs(void);          // Initialize Inputs
uint8_t ReadInput(int Input);   // Read Inputs

#endif