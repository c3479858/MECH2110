#include <Servo.h>

#define SERVOPIN 8  // servo pins for excavator arm
#define SERVOPIN 9
#define SERVOPIN 10

Servo bucket;  //pos1
Servo middle;  //pos2
Servo boom;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  bucket.attach(8);  // max 135 // 0-, 0 is down, 90 is store,
  middle.attach(9);  // max 108 // 0 is store, 150 is max
  boom.attach(10);   // max = 105 // 110 is store, 0 is extension
  delay(100);

boom.write(150);
middle.write(0);
bucket.write(45);



}


void loop() {
  // put your main code here, to run repeatedly:
}
