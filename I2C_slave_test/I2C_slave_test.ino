// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(8);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while(Wire.available() > 0){

    if(Wire.available() == 2)
    {
      int x = Wire.read();
      Serial.print("X: ");
      Serial.println(x);
    }
    else if(Wire.available() == 1)
    {
      int y = Wire.read();
      Serial.print("Y: ");
      Serial.println(y);
    }
  }
}
