#include <AccelStepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define motorInterfaceType 4

AccelStepper stepper = AccelStepper(motorInterfaceType, IN1, IN2, IN3, IN4);

void setup() {
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(200);
  stepper.setAcceleration(512);
  stepper.moveTo(500);
}

void loop() {
  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run();
}
