#include <Wire.h>
int transmissionSampling = 50;

int x = 100;
int y = 100;

void setup() {
  Wire.begin(); // join I2C bus (address optional for master)
}

void loop() {
  randEye();
  send(x, y);
}

void randEye() {
  x = random(0, 100);
  y = random(0, 100);
}

void send(int x, int y) {
  Wire.beginTransmission(8); // device address #8
  Wire.write(x);
  Wire.write(y);
  Wire.endTransmission();
  delay(transmissionSampling);
}