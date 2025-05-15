#include <Servo.h>
Servo tapServo;

void setup() {
  tapServo.attach(16);
  tapServo.write(0);
}

void loop() {
  tapServo.write(90);
  delay(500);
  tapServo.write(0);
  delay(1000);
}