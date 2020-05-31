#include "Arduino.h"

#ifndef COMMS_H_
#define COMMS_H_

// Device Names
#define MB1 1
#define MB2 2
#define WFI 3
#define DBG 4

// MODBUS Channels
// Serial2
#define MAX485_1_RX 17 
#define MAX485_1_TX 16
#define MAX485_1_EN 19
// Serial3
#define MAX485_2_RX 15
#define MAX485_2_TX 14
#define MAX485_2_EN 18

// WiFi Channels
#define ESP8266_RX  35 // (RX -> TX of Arduino)
#define ESP8266_TX  34 // (TX -> RX of Arduino)

void InitComms(bool MB1 = true, bool MB2 = true, bool WFI = true, bool DBG = true); 
void SendData(char payload, uint8_t device = 0);
char ReceiveData(uint8_t device = 0);

#endif