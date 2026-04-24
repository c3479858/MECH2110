#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDR 9


String command = "";
bool isDone = true;

const int buttonPin = 6;
int buttonState = 0;

Servo bucket;  // 8
Servo middle;  // 9
Servo boom;    // 10

int IN1 = 7;  // for stepper motor under excavator arm
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;
int ENA = 3;
int ENB = 2;


void setup() {
  Wire.begin(SLAVE_ADDR);  //makes this arduino a slave
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);

  bucket.attach(8);  //bucket pin number
  middle.attach(9);
  boom.attach(10);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
}

void requestEvent() {
  if (isDone) {
    Wire.write("DONE");
  } else {
    Wire.write("BUSY");
  }
}

void receiveEvent(int bytes) {
  command = "";

  while (Wire.available()) {
    command += (char)Wire.read();
  }

  Serial.println(command);


  if (command == "BUTTON") {
    isDone = false;
    if (buttonState == LOW) {
      isDone = true;
    }


    if (command == "START") {
      isDone = false;
      //set stepper motor to around
      for (int i = 45; i >= 0; i--) {
        bucket.write(i);
        delay(50);  // bigger delay will slow it
      }
      for (int i = 110; i >= 70; i--) {
        boom.write(i);
        delay(50);
      }
      isDone = true;
    }

    if (command == "EXTEND") {
      isDone = false;
      for (int i = 0; i <= 30; i++) {  // can write as -= 2 or any integer
        middle.write(i);
        delay(50);
      }
      for (int i = 70; i >= 60; i--) {  // can write as -= 2 or any integer
        boom.write(i);
        delay(50);
      }
      for (int i = 30; i <= 60; i++) {  // can write as -= 2 or any integer
        middle.write(i);
        delay(50);
      }
      for (int i = 0; i <= 30; i++) {
        bucket.write(i);
        delay(50);  // bigger delay will slow it
      }
      for (int i = 60; i >= 40; i--) {  // can write as -= 2 or any integer
        boom.write(i);
        delay(50);
      }
      for (int i = 60; i <= 80; i++) {  // can write as -= 2 or any integer
        middle.write(i);
        delay(50);
      }
      for (int i = 30; i >= 20; i--) {
        bucket.write(i);
        delay(50);
      }
      for (int i = 40; i >= 20; i--) {  // can write as -= 2 or any integer
        boom.write(i);
        delay(50);
      }
      for (int i = 80; i <= 100; i++) {  // can write as -= 2 or any integer
        middle.write(i);
        delay(50);
      }
      for (int i = 100; i <= 130; i++) {  // can write as -= 2 or any integer
        middle.write(i);
        delay(50);
      }
      for (int i = 20; i <= 90; i++) {
        bucket.write(i);
        delay(50);
      }
      isDone = true;
    }

    if (command == "BUCKETUP") {
      isDone = false;
      for (int i = 20; i <= 110; i++) {
        boom.write(i);
        delay(50);
      }
      for (int i = 90; i <= 130; i++) {
        bucket.write(i);
        delay(50);
      }
      for (int i = 130; i <= 0; i--) {
        middle.write(i);
        delay(50);
      }
      isDone = true;
    }

    if (command == "DUMP") {
      isDone = false;
      for (int i = 130; i >= 45; i--) {
        bucket.write(i);
        delay(50);
        isDone = true;
      }
    }
    if (command == "UP") {
      isDone = false;
      for (int i = 0; i <= 130; i++) {
        bucket.write(i);
        delay(50);
        isDone = true;
      }
    }
  }
}
