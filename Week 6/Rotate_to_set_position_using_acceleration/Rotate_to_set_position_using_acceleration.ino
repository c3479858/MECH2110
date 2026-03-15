#include <AccelStepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define motorInterfaceType 4

AccelStepper stepper = AccelStepper(motorInterfaceType, IN1, IN3, IN2, IN4);

void setup() {
}

void loop() {
  switch(case_var) {
    case 1:
      case_description = "one clockwise revolution"
      if (stepper.distanceToGo() == 0)
        stepper.moveTo()
  }
}