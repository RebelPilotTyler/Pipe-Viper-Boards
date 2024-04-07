//Transceiver LED Code, a program for testing the transceivers for Pipe Viper. This code is for the receiver only.
//Written by Tyler Widener (tylerwidenerlm@gmail.com) and Glenn Truett.

//======Libraries======
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//======Variables======
RF24 radio(8, 7);  // CE, CSN
const byte address[6] = "00001";
const int ledPin = 6;

//=========Main========
void setup() {
  pinMode(ledPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);
  
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    if (text == "LED ON") {
      Serial.println("LED ON");
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
  }
}