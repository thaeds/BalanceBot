#include "dxl_hal.h"
#include "dynamixel.h"

void setup() {
  dxl_hal_open(0, 9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  Serial.println();
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
  digitalWrite(13, HIGH);
}
