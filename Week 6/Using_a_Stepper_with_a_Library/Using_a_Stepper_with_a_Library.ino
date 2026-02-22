#include <AccelStepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define motorInterfaceType 4

AccelStepper stepper = AccelStepper(motorInterfaceType, IN1, IN2, IN3, IN4);

void setup() {

  stepper.setMaxSpeed(1000);
  stepper.setSpeed(256);

}

void loop() {

  stepper.runSpeed();

}
