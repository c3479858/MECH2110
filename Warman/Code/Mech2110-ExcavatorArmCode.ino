#include <Servo.h>
#include <Wire.h>

#define SERVOPIN 8  // servo pins for excavator arm
#define SERVOPIN 9
#define SERVOPIN 10

int IN1 = 7;
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;
int ENA = 3;
int ENB = 2;

Servo bucket;  //pos1
Servo middle;  //pos2
Servo boom;    //pos3

int trigPin = 11;  // ultrasonic sensor pins for bucket
int echoPin = 12;
unsigned long previousMillis = 0;
const long interval = 60; // delay between readings

float distanceMM;                  // variable for ultrasonic calculation
long duration;                     // variable for ultrasonic calculation
int currentAngle = middle.read();  // for the middle servo to be able to adjust a variable

int stages = 0;      // for switches to go from rock collection, to ramp, to finish, etc
int collection = 0;  // for rock collection
int speed = 30;      // speed value for our middle servo



void excavator_extension() {
  // void defines the function, to call we need the name of the functipn "excavator_extension"
  // followed by ()
  bucket.write(180);  // bucket 180 so its flat against surface  // need to define an extension to run this so it can just be called on. Also
  middle.write(90);   //
  boom.write(90);
  delay(1000);
}

void excavator_extension2() {  // full distance
  bucket.write(180);           // could put delays in middle if needed
  middle.write(180);
  boom.write(180);
  delay(1000);
}

void boom_drawback() {
  for (int i = 180; i >= 0; i--) {  //this will bring the middle connection back at a set rate by moving through each step/degree
                                    //could also use the VarSpeedServo library, myServo.slowmove(180,30) / moves 180 degrees at a rate of 30
    boom.write(i);
    delay(50);  //increasing this delay will make it slower
    // i can just add i values into the running code as the untrasonic sensor picks up the ground
    // if US distance is >10 i--, might need to use Var Speed so i can slow the motor
  }
}

void ultrasonic_sensor() {
  // send trig to HIGH to send out an ultrasonic burst
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //10 is lowest
  digitalWrite(trigPin, LOW);

  //read the echo pin, pulseIn() returns the travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //calculation distance
  // Speed of sound - 0.034 cm/uS or 0.343 mm/uS
  distanceMM = duration * 0.343 / 2;  // the /2 is for the distance out and back

  Serial.print("Distance: ");
  Serial.print(distanceMM);
  Serial.println(" mm");
}

void middle_drawback() {
  float dist = distanceMM;
  if (dist > 200) {
    currentAngle += 1;
  } else if (dist < 100) {
    currentAngle -= 1;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bucket.attach(8);  //bucket pin number
  middle.attach(9);
  boom.attach(10);

  bucket.write(0);  // set servos to there related 0 value, values will need to be adjusted accordingly
  middle.write(0);
  boom.write(0);
  delay(100);

  pinMode(trigPin, OUTPUT);  // sets trig as output and echo as input. trig sends out sound, echo recieves it
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);  //clear the trigger pin by setting it to low for a clean pulse
  delayMicroseconds(2);
}

void loop() {
  switch (stages) {
    case (0):;  /// getting to rock collection
      {
        stages++;
      }
      break;
    case (1):;  // rock collection
      {
        switch (collection) {
          case (0):;  //extension
            {
              Serial.println("Extension 1");
              excavator_extension();
              delay(100);

              collection++;
            }
            break;

          case (1):;  //pulling back
            {
              Serial.println("Drawback 1");
              ultrasonic_sensor();
              boom_drawback();
              middle_drawback();           //adjusts current angle
              middle.write(currentAngle);  // moves servo
              delay(100);

              collection++;
            }
            break;

          case (2):;
            {  // lifting up, could use either mapping or just sent servo angles with for to make it smooth
              collection++;
            }
            break;

          case (3):;
            {  // rotating around + dump + rotate back
              collection++;
            }
            break;

          case (4):;
            {  //second extension
              excavator_extension2();
              delay(100);

              collection++;
            }
            break;
          
          case (5):;
          { // second drawback
            ultrasonic_sensor();
            boom_drawback();
            middle_drawback();           //adjusts current angle
            middle.write(currentAngle);  // moves servo
            delay(100);

            collection++;
          }
          break;

          case(6):;
          { // second pick up
            //
          }
          break;

          case(7):;
          { // second rotate + drop + finish position
            //
          }
          break;
        }
      }
  }
}
