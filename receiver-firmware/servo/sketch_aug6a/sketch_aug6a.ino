#include <Servo.h>

const int SERVO_PIN = 0;

Servo flipper;

void setup() {
  flipper.attach(SERVO_PIN);
  flipper.writeMicroseconds(1000);
  delay(1000);
}

void loop() {
  flipper.writeMicroseconds(1100);
  delay(1000);
  flipper.writeMicroseconds(1600);
  delay(1000);
  flipper.writeMicroseconds(1900);
  delay(1000);
}