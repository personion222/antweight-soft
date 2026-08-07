#include <ESP32Servo.h>

const int SERVO_PIN = D8;

Servo flipper;

void setup() {
	flipper.attach(SERVO_PIN);
	flipper.writeMicroseconds(1000);
}

void loop() {}
