#include <AccelStepper.h>

// 4-wire bipolar mode
#define MotorInterfaceType 4
int currentpos = 0;
// IN1, IN2, IN3, IN4 from L298N
AccelStepper stepper(MotorInterfaceType, 5, 4, 6, 7);

void setup() {
  stepper.setMaxSpeed(600);  // keep moderate for L298N
  stepper.setAcceleration(300);
  stepper.moveTo(currentpos - 512);
  stepper.runToPosition();
  delay(5000);
}

void loop() {

}
