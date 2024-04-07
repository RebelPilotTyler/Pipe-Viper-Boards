//Mesh_Bot_Code, a program to test the mesh network for Pipe Viper.
//This program is for the BOT NODE, meaning the END RECEIVER.
//Written for Pipe Viper, a pipe inspection robot for AMKA Services.
//Written by Tyler Widener, tylerwidenerlm@gmail.com, assisted by ChatGPT.

//Libraries
#include <SPI.h>
#include "printf.h"
#include <RF24.h>
#include <string.h>

//Variables and Initializations
#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN
const int LEDPin = 6;
uint8_t address[][6] = { "1Node", "2Node", "3Node", "4Node", "5Node", "6Node" };
int radioNumber = 5;
bool role = false;
int payload = 0; //String length of 20 characters

//Main
void setup() {
  Serial.begin(115200);
  //while (!Serial) { //While loop waiting for serial comms removed for mobile system

  //}
  if (!radio.begin()) {
    Serial.println(F("Radio Not Responding!"));
    while(1) {}
  }
  Serial.println(F("Pipe Viper Bot"));
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(sizeof(payload));
  radio.setDataRate(RF24_250KBPS); // ADDED setDataRate() for increased range
  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(0, address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.openReadingPipe(2, address[2]);
  radio.openReadingPipe(3, address[3]);
  radio.openReadingPipe(4, address[4]);
  radio.openReadingPipe(5, address[5]);

  pinMode(LEDPin, OUTPUT); //Add the button as an input pin

  if (role) {
    radio.stopListening();
  }
  else {
    radio.startListening();
  }
}

void loop() {
  /*
  while(digitalRead(buttonPin) == LOW) { //While loop to wait to transmit until button is pressed
      //wait for button to be pressed
      network.update();
      mesh.update();
  }

  unsigned long start_timer = micros();                // start the timer
  //bool report = radio.write(&payload, sizeof(payload));  // transmit & save the report
  bool report = network.write(header, &payload, sizeof(payload));
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
*/
  uint8_t pipe;
  if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    digitalWrite(LEDPin, HIGH);
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(&payload, bytes);             // fetch payload from FIFO
    Serial.print(F("Received "));
    Serial.print(bytes);  // print the size of the payload
    Serial.print(F(" bytes on pipe "));
    Serial.print(pipe);  // print the pipe number
    Serial.print(F(": "));
    Serial.println(payload);  // print the payload's value
    delay(1000);
    digitalWrite(LEDPin, LOW);
  }
/*
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
  }
*/
  // to make this example readable in the serial monitor
  //delay(1000);  // slow transmissions down by 1 second
}