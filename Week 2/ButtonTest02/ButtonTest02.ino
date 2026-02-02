#define button 2
const int ledPin = 13;
const int buttonPin = 2;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  unsigned long Start_time = millis();

  while (digitalRead(buttonPin) == 1) {
    if(millis() < Start_time + 2000) {
      digitalWrite(ledPin, HIGH);
    }
    else if (millis() > Start_time + 2000) {
      digitalWrite(ledPin, LOW);
    }
    Start_time = millis();
  }
}

void loop() {

  Serial.println(digitalRead(buttonPin));
  delay(100);
  Serial.println(millis());

}