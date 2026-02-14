#include <Servo.h>// The use of the library disables analogWrite() (PWM) 
//functionality on pins 9 and 10, whether or not there is a Servo on those pins.

#define SERVOPIN 10

Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
int dir = 0; // variable to store the servo direction
int posFinal = 90; //max angle for sweep
int posInitial = 0; //min angle for sweep

void setup() {
    
  Serial.begin(115200);
  myservo.attach(SERVOPIN); // initialises the servo by attatching the servo on pin
//10 to the servo object
}
/*void loop() {
  
  if(dir == 0) {
    if(pos<posFinal) {
      pos++;
    }
    else {
      dir = 1;
      pos = posFinal - 1;
    }
  }
  else {

    if(pos>posInitial) {
      pos--;
    }
    else {
      dir = 0;
      pos = posInitial + 1;
    }
  }

  myservo.write(pos);

  Serial.print("Position="); //print to the serial monitor
  Serial.println(pos);  //prints the position to the serial monitor + a new line

  delay(15);            // waits 15ms for the servo to reach the position

}
*/
void loop() {
  myservo.write(0);
  Serial.println(myservo.read());
  delay(1000);
  myservo.write(90);
  Serial.println(myservo.read());
  delay(500);
  myservo.write(0);
  Serial.println(myservo.read());
  delay(500);
  myservo.write(180);
  Serial.println(myservo.read());
  delay(1000);
}