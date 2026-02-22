// Define a stepper and the pins it will use
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

int step_delay = 4000;  // setting this below 2000 may cause the stepper to not spin

void loop() {

  step_delay = 5000;
  for (int i = 0; i <= 256; i++) {

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delayMicroseconds(step_delay);

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delayMicroseconds(step_delay);

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
    delayMicroseconds(step_delay);

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
    delayMicroseconds(step_delay);
  }
  delay(1000);

  step_delay = 2500;
  for (int i = 0; i <= 512; i++) {

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);

    delayMicroseconds(step_delay);
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
    delayMicroseconds(step_delay);

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delayMicroseconds(step_delay);

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delayMicroseconds(step_delay);
  }
  delay(1000);
}