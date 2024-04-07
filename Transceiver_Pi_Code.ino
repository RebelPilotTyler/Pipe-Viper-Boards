//Transceiver Pi Code, a program for testing the transceivers for Pipe Viper. This program is for the bot only.
//Written by Tyler Widener (tylerwidenerlm@gmail.com)

//UPDATE 2.0:
//Switched over to using a button and LED, as well as being powered by it's own power source.
//This allows for more mobile tests of the transceivers, since it won't require a laptop.

//FIXME Circuit Notes:
//Add 10uF Capacitor to Transceiver VCC and GND, for Power Regulation.
//Wire Main GND to extra silver GND ports, for extra grounding.
//Possibly use external 3.3V power source for more stable power.

//Libraries
#include <SPI.h>
#include "printf.h"
#include <RF24.h>
#include <string.h>

// Variables and Initializations
#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN
const int ledPin = 6;
uint8_t address[][6] = { "1Node", "2Node" };
bool radioNumber = 1;
bool role = false;
int payload = 0;

void setup() {
  Serial.begin(115200);
  //while (!Serial) {  //While loop for serial comms removed for Update 2.0 testing

  //}
  if (!radio.begin()) {
    //Serial.println(F("Radio Not Responding!"));
    while(1) {}
  }
  Serial.println(F("Pipe Viper Bot"));
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(sizeof(payload));
  radio.setDataRate(RF24_250KBPS); // ADDED setDataRate() for increased range
  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(1, address[!radioNumber]);

  pinMode(ledPin, OUTPUT); //Set the LED pin to an output

  if (role) {
    radio.stopListening();
  }
  else {
    radio.startListening();
  }
}

void loop() {
  if (role) {
    // This device is a TX node

    while (!Serial.available()) {
      //wait for user input
    }
    payload = Serial.read();

    unsigned long start_timer = micros();                // start the timer
    bool report = radio.write(&payload, sizeof(payload));  // transmit & save the report
    unsigned long end_timer = micros();                  // end the timer

    if (report) {
      Serial.print(F("Transmission successful! "));  // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);  // print the timer result
      Serial.print(F(" us. Sent: "));
      Serial.println(payload);  // print payload sent
    } else {
      Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
      radio.read(&payload, bytes);             // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);  // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);  // print the pipe number
      Serial.print(F(": "));
      Serial.println(payload);  // print the payload's value

      digitalWrite(ledPin, HIGH); //Flash the LED to acknowledge that a message has been received.
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
  }  // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();
    }
  }
}