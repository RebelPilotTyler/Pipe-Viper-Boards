// Transceiver Anchor HP (High Power) Code, a program for testing the transceivers for Pipe Viper.
// This program is for the ANCHOR (Computer) ONLY!
// Written by Tyler Widener, tylerwidenerlm@gmail.com, assisted by ChatGPT.

// Libraries
#include <SPI.h>
#include <RH_RF95.h> // RadioHead library for RF95 module

// Variables and Initializations
#define CS_PIN 8 // Define the CS (Chip Select) pin
#define RESET_PIN 2 // Define the Reset pin
#define CE_PIN 7 //The Chip Enable pin, which is manually managed. HIGH turns the transceiver on, LOW turns it off

const int buttonPin = 6; //The pin the button is connected to

int payload = 0; //Variable to send, can be any number

RH_RF95 rf95(CS_PIN, RESET_PIN); // Initialize the RF95 module

void setup() {
  pinMode(buttonPin, INPUT);
  //pinMode(CE_PIN, OUTPUT);
  //digitalWrite(CE_PIN, HIGH);
  delay(500);
  Serial.begin(115200);
  if (!rf95.init()) { //Check to make sure the transceiver initialized properly.
    Serial.println("Initialization Failure");
    while (1);
  }
  Serial.println("Pipe Viper Anchor - High Power");
}

void loop() {
  while (digitalRead(buttonPin) == LOW) {} // Block program until the button is pressed!

  rf95.send((uint8_t*)payload, sizeof(payload)); // Send payload
  rf95.waitPacketSent(); //Wait to send another message until the previous one is sent.


  /* Program for receiving a message, commented out as this is the anchor.
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Received: ");
      Serial.println((char*)buf);
    }
  }
  */
}
