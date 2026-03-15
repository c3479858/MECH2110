//Libraries
#include <Servo.h>  //disables analogWrite() on pins 9 and 10
#include <AccelStepper.h>

//Pin Assignments
#define buttonPin 2  //button
#define dc_IN1 3     //DC motor IN1
#define dc_IN2 4     //DC motor IN2
#define dc_ENA 5     //DC motor ENA      //Needs a PWM pin
#define IN1 6        //Stepper IN1
#define IN2 7        //Stepper IN2
#define IN3 8        //Stepper IN3
#define IN4 11       //Stepper IN4
#define servoPin 10  //Servo             //Needs a PWM (either 9 or 10)
#define ledPin 13    //built in LED

//Misc
#define motorInterfaceType 4
AccelStepper stepper = AccelStepper(motorInterfaceType, IN1, IN3, IN2, IN4);

unsigned long startTime = millis();

Servo myservo;

int max = 255;
int speed = 0;

String case_description = "default";

int task = 0;                               //set to 1 to start if push button start isnt appreciated

void setup() {

  Serial.begin(9600);

  //TASK 1
  myservo.attach(servoPin);

  //TASK 2
  pinMode(ledPin, OUTPUT);  //Change to LED_BUILTIN if this doesn't work, could remove the definition as well if so.
  pinMode(buttonPin, INPUT_PULLUP);
  //unsigned long startTime = millis();

  //TASK 3
  pinMode(dc_IN1, OUTPUT);
  pinMode(dc_IN2, OUTPUT);
  pinMode(dc_ENA, OUTPUT);

  //TASK 4
  //stepper.setAcceleration(50);
  //stepper.setMaxSpeed(500);   //max speed is not given, enable if stepper not working

  //TASK 5
  //none needed (?)
}

void loop() {

  switch (task) {
    case 1:
      case_description = "servo to 15, wait 1.5s, servo to 70, wait 2s. After 4 cycles, +1 to task var";
      int i = 0;
      while (i < 4) {
        myservo.write(15);  //servo to 15deg
        delay(1500);        //wait 1.5s
        myservo.write(70);  //servo to 70deg
        delay(2000);        //wait 2s
        i++;
      }
      task++;  //advance the task count

    case 2:
      case_description = "blink led, on 3s, off 3s. Instant button press turns off, prints text and +1 to task var.";
      while (digitalRead(buttonPin) == 1) {  //while button isnt pressed
        startTime = millis();
        if (millis() < startTime + 3000) {  //on, wait 3s
          digitalWrite(ledPin, LOW);
        } else if (millis() < startTime + 6000) {  //off, wait 3s
          digitalWrite(ledPin, HIGH);
        } else {
          startTime = millis();  //loop
        }
      }
      task++;  //when button pressed, +1 to task counter

    case 3:
      case_description = "dc to 50% clkws for 4s, button turns motor off and +1 to task.";
      speed = 0.5 * max;           //dc speed set
      goForwards();                //direction set
      analogWrite(dc_ENA, speed);  //writing to motor
      delay(4000);
      if (digitalRead(buttonPin) == 0) {  //not sure if this will work, might need to be reversed while statement i.e. while button pressed, dont advance task
        breakStop();
      }
      task++;

    case 4:
      case_description = "wait 2s, dc anticlkws at 80% for 8s: after 1s, accel stepper at 50s/s/s clkws for 8 rev. Once everything stopped +1 to task.";
      speed = 0.8 * max;     //80% max speed
      delay(2000);           //wait 2s
      startTime = millis();  //resetting start time
      goBackwards();
      while (millis() < startTime + 8000) {  //not sure if this will work, test in lab!!!!!!!!!!!!!!!!!!!!!!!
        analogWrite(dc_ENA, speed);          //write speed to motor
      }
      delay(1000);
      stepper.setAcceleration(50);
      stepper.moveTo(2048 * 8);
      stepper.run();
      delay(7000);  //unsure if this will wait for the stepper to finish before starting the countdown, test in lab.
      coastStop();
      /*      if (stepper.distanceToGo() == 0) {
        task++;
      }*/
      while (stepper.distanceToGo() != 0) {
      }
      task++;

    case 5:
      case_description = "wait 2s, accelerate stepper@3000s/s/s anticlkws at max speed of 200s/s, after 6 rev stop and set case to 0.";
      delay(2000);
      stepper.setAcceleration(3000);
      stepper.setMaxSpeed(200);
      stepper.moveTo((2048 * (8 - 6)));
      stepper.run();
      /*      if (stepper.distanceToGo() == 0) {      //might not work since itll just skip this line i think *shrug*
        task = 0;                               //not necessary but wanted to flex B)
    }*/
      while (stepper.distanceToGo() != 0) {
      }
      task = 0;

    case 0:
      case_description = "default case, press the button to start from the beginning again.";
      while (digitalRead(buttonPin) == 1) {
      }
      task++;
  }
}
void goForwards() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void goBackwards() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void coastStop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}
void breakStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}