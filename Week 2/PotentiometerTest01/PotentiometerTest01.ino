#define pot A0

const int ledPin = 13;
const int analogPin = A0;

const float V_REF = 5.0;  //reference voltage
const float B_REF = 1023.0;  //reference bit

void setup() {
  Serial.begin(9600); //initialise serial

  pinMode(ledPin, OUTPUT);
  pinMode(analogPin, INPUT);
}

int reading = 0;
float voltage = 0;

void loop() {

  delay(200);

  reading = analogRead(analogPin);

  Serial.print("Reading = ");
  Serial.println(reading);

  voltage = (reading / B_REF) * V_REF;

  if (voltage <= 1.000 ) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Voltage = ");
  Serial.print(voltage, 3);
  Serial.println("V");
}
