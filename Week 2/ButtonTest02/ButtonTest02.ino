#define button 2
const int ledPin = 13;
const int buttonPin = 2;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  unsigned long Start_time = millis();

  while (digitalRead(buttonPin) == 1) { //when button is not pressed...
  
    if(millis() < Start_time + 2000) {  //wait for 2 seconds with LED off
      digitalWrite(ledPin, LOW);
    }

    else if (millis() < Start_time + 3000) {  //turn LED on for 1 second
      digitalWrite(ledPin, HIGH);
    }

    else {
      Start_time = millis();  //resets the to the first if loop to complete the infinite loop
    }

  }

  digitalWrite(ledPin, LOW);  //turns the LED off when the while loop isnt true

}

void loop() {

  Serial.println(digitalRead(buttonPin));
  delay(100);

}