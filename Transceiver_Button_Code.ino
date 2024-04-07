//Transceiver Button Code, a program for testing the transceivers for Pipe Viper. This code is for the transmitter only.
//Written by Tyler Widener (tylerwidenerlm@gmail.com) and Glenn Truett.

//Libraries
#include <SPI.h>
#include "printf.h"
#include <RF24.h>

RF24 radio(8, 7);  // CE, CSN
const byte address[6] = "00001";
const int buttonPin = 6;

void setup() {
  
}

void loop() {
  
}