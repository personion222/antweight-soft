#include <Servo.h>

const int SERVO_PIN = 0;

Servo flipper;

void setup() {
  flipper.attach(SERVO_PIN);
  flipper.writeMicroseconds(500);
  delay(1000);
}

void loop() {
  flipper.writeMicroseconds(600);
  delay(1000);
  flipper.writeMicroseconds(700);
  delay(1000);
  flipper.writeMicroseconds(800);
  delay(1000);
}