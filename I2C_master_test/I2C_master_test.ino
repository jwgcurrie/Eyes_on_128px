#include <Wire.h>

void setup() {
  Wire.begin(); // join I2C bus (address optional for master)
}

int x = 100;
int y = 100;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(x);
  Wire.write(y);
  Wire.endTransmission();    // stop transmitting
  delay(500);
}