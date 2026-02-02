#define button 2
const int ledPin = 13;
const int buttonPin = 2;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  while (digitalRead(buttonPin) == 1) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
}

void loop() {

  delay(100);
  Serial.println(millis());

}
