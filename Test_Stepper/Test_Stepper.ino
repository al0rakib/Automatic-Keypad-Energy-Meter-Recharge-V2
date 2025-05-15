#include <AccelStepper.h>

AccelStepper stepperX(AccelStepper::FULL4WIRE, 5, 4, 14, 12);
AccelStepper stepperY(AccelStepper::FULL4WIRE, 13, 15, 0, 2);

void setup() {
  Serial.begin(115200);
  stepperX.setMaxSpeed(500); stepperX.setAcceleration(300);
  stepperY.setMaxSpeed(500); stepperY.setAcceleration(300);
}

void loop() {
  stepperX.moveTo(200); stepperY.moveTo(200);
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run(); stepperY.run();
  }
  delay(1000);
  stepperX.moveTo(0); stepperY.moveTo(0);
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run(); stepperY.run();
  }
  delay(1000);
}