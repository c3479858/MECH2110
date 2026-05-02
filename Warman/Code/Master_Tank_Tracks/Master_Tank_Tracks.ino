#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDR 9
bool slaveDone = false;
int stages = 0;

// RHS

int IN1R = 2;
int IN2R = 3;
int IN3R = 4;
int IN4R = 5;
int ENAR = 6;
int ENBR = 7;

// LHS

int IN1L = 8;
int IN2L = 9;
int IN3L = 10;
int IN4L = 11;
int ENAL = 12;
int ENBL = 13;


void sendCommand(const char* cmd) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(cmd);
  Wire.endTransmission();
}

String requestResponse() {
  String response = "";

  Wire.requestFrom(SLAVE_ADDR, 10);  //requesting up to 10 bytes, 10 characters??

  while (Wire.available()) {
    char c = Wire.read();
    response += c;
  }
  return response;
  Serial.println("Got response");
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);
  pinMode(IN3R, OUTPUT);
  pinMode(IN4R, OUTPUT);
  pinMode(ENAR, OUTPUT);
  pinMode(ENBR, OUTPUT);

  pinMode(IN1L, OUTPUT);
  pinMode(IN2L, OUTPUT);
  pinMode(IN3L, OUTPUT);
  pinMode(IN4L, OUTPUT);
  pinMode(ENAL, OUTPUT);
  pinMode(ENBL, OUTPUT);
}



void loop() {
  switch (stages) {
    case (0):;
      {
        sendCommand("BUTTON");
        Serial.println("Awaiting Start");
        slaveDone = false;

        while (!slaveDone) {
          String response = requestResponse();

          if (response == "DONE")
            ;
          slaveDone = true;
          Serial.println("Ready Position Complete");
          delay(100);
          stages++;
          stages++;
        }
      }
    case (1):;
      {  // send message to servos for collection
        sendCommand("START");
        Serial.println("Ready position");
        slaveDone = false;

        while (!slaveDone) {
          String response = requestResponse();

          if (response == "DONE")
            ;
          slaveDone = true;
          Serial.println("Ready Position Complete");
          delay(100);
          stages++;
        }
      }
    case (2):;
      {  // arm extension in dump zone
        sendCommand("Extend");
        Serial.println("Extending");
        slaveDone = false;
        while (!slaveDone) {
          String response = requestResponse();

          if (response == "DONE")
            ;
          slaveDone = true;
          Serial.println("Extension Complete");
          delay(100);
          stages++;
        }
      }

    case (3):;
      {  // bucket tilt up
        sendCommand("BUCKETUP");
        Serial.println("BUCKET UP");
        slaveDone = false;
        while (!slaveDone) {
          String response = requestResponse();

          if (response == "DONE")
            ;
          slaveDone = true;
          Serial.println("Rocks are high");
          delay(100);
          stages++;
        }
      }
    case (4):;
      {  //backwards movement
        Serial.println("Moving away from dump zone");
        backwards();
        analogWrite(ENAR, 150);
        analogWrite(ENBR, 150);
        analogWrite(ENAL, 150);
        analogWrite(ENBL, 150);
        delay(500); ////////////////////////////////
        stop();
        delay(100);
        stages++;
      }

    case (5):;
      {  //turning
        Serial.println("Turning");
        lturn();
        analogWrite(ENAR, 150);
        analogWrite(ENBR, 150);
        analogWrite(ENAL, 150);
        analogWrite(ENBL, 150);
        delay(1100); ///////////////////////////////
        stop();
        delay(100);
        stages++;
      }
    case (6):;
      {  // going up ramp
        forwards();
        analogWrite(ENAR, 150);
        analogWrite(ENBR, 150);
        analogWrite(ENAL, 150);
        analogWrite(ENBL, 150);
        delay(3000); /////////////////////////////
        stop();
        delay(100);
        stages++;
      }
    case (7):;
      {  // bucket dump
        sendCommand("DUMP");
        Serial.println("DUMPING");
        slaveDone = false;
        while (!slaveDone) {
          String response = requestResponse();

          if (response == "DONE")
            ;
          slaveDone = true;
          Serial.println("Rocks are down, I repeat, rocks are down");
          delay(100);
          stages++;
        }
      }
    case (8):;
      {  // going up ramp
        forwards();
        analogWrite(ENAR, 150);
        analogWrite(ENBR, 150);
        analogWrite(ENAL, 150);
        analogWrite(ENBL, 150);
        delay(2000);  ////////////////////////////
        stop();
        delay(100);
        stages++;
      }
    case (9):;
      {  // doing down the ramp
        backwards();
        analogWrite(ENAR, 100);
        analogWrite(ENBR, 100);
        analogWrite(ENAL, 100);
        analogWrite(ENBL, 100);
        delay(2000);
        stop();
        delay(100);
        stages++;
      }
    case (10):;
      {
        // led
      }
  }
}


void forwards() {
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);

  digitalWrite(IN3R, HIGH);
  digitalWrite(IN4R, LOW);

  digitalWrite(IN1L, LOW);
  digitalWrite(IN2L, HIGH);

  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
}

void backwards() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);

  digitalWrite(IN3R, LOW);
  digitalWrite(IN4R, HIGH);

  digitalWrite(IN1L, HIGH);
  digitalWrite(IN2L, LOW);

  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}
void stop() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, LOW);

  digitalWrite(IN3R, LOW);
  digitalWrite(IN4L, LOW);

  digitalWrite(IN1R, LOW);
  digitalWrite(IN2L, LOW);

  digitalWrite(IN3R, LOW);
  digitalWrite(IN4L, LOW);
  analogWrite(ENAR, 0);
  analogWrite(ENBR, 0);
  analogWrite(ENAL, 0);
  analogWrite(ENBL, 0);
}

void lturn() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);

  digitalWrite(IN3R, LOW);
  digitalWrite(IN4R, HIGH);

  digitalWrite(IN1L, LOW);
  digitalWrite(IN2L, HIGH);

  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
}
