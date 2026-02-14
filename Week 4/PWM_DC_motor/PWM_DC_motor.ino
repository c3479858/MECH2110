#define IN1 3
#define IN2 4
#define ENA 9

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  goForwards();
  for (int i = 0; i <= 255; i++) {
    analogWrite(ENA, i);
    delay(10);
  }
  
  analogWrite(ENA, 255);
  delay(2500);

  for (int i = 255; i >= 0; i--) {
    analogWrite(ENA, i);
    delay(10);
  }
  goBackwards();
  for (int i = 0; i <= 255; i++) {
    analogWrite(ENA, i);
    delay(10);
  }
  
  analogWrite(ENA, 255);
  delay(2500);

  for (int i = 255; i >= 0; i--) {
    analogWrite(ENA, i);
    delay(10);
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