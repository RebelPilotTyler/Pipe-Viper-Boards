// Transceiver Bot HP (High Power) Code, a program for testing the transceivers for Pipe Viper.
// This program is for the BOT (Receiver) ONLY!
// Written by Tyler Widener, tylerwidenerlm@gmail.com, assisted by ChatGPT.

// Libraries
#include <SPI.h>
#include <RH_RF95.h> // RadioHead library for RF95 module

// Variables and Initializations
#define CS_PIN 7 // Define the CS (Chip Select) pin
#define RESET_PIN 8 // Define the Reset pin

const int ledPin = 6; //The pin the button is connected to

int payload = 0; //Variable to send, can be any number

RH_RF95 rf95(CS_PIN, RESET_PIN); // Initialize the RF95 module

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  if (!rf95.init()) { //Check to make sure the transceiver initialized properly.
    Serial.println("Initialization Failure.");
    while (1);
  }
  Serial.println("Pipe Viper Anchor - High Power");
}

void loop() {
  // Program for receiving a message, commented out as this is the anchor.
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Received: ");
      Serial.println((char*)buf);
    }
  }

  /* Program for sending message, commented out as this is the receiver
  rf95.send(&payload, sizeof(payload)); // Send payload
  rf95.waitPacketSent(); //Wait to send another message until the previous one is sent.
  */
}
