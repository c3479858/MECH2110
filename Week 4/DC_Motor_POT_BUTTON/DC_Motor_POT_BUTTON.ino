/*
   MECH 2110 - Lab 2
   DC motor
*/
#define IN1 3
#define IN2 4
#define ENA 9
#define POT A0
#define BUTTON 2

void setup() {  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}
bool button_released = true;
int case_var = 1;          // var is the variable used for the switch case
String case_description = "Motor foward";
unsigned long last_time_pressed = millis(); // this variable stores the millis when a button is pressed and is used to calculate how long the motor has been spinning for
unsigned long time_since_last_pressed = 0;  // this variable is used to store how long the motor has been spinning for after a button press
int value = 0;        // value is the varable for the ouput of the map function
int motor_power = 0;  //This variable will be sent to the serial monitor do that you can see what value is being sent to the ENA pin of the motor driver

// The variables bellow will be used to for the map function which re-maps a number from one range to another
int fromLow = 0;   //This should be the lowest value that you expect to see from the potentiometer
int fromHigh = 1024;  //This should be the Highest value that you expect to see from the potentiometer
int toLow = 20;     //This should be the lowest Value where the motor just start to spin you may have to adjust this value after intal testing
int toHigh = 255;    //This should be the highest value that you can send to the motor controller

void loop() {  //Put your main code here, to run repeatedly:
  switch (case_var) {
    case 1:  // when var == 1 do this
      case_description = "Motor foward ";
      goForwards();
      value = analogRead(POT);                                    // reads the value from the pot and saves to a variable for re-mapping
      motor_power = map(value, fromLow, fromHigh, toLow, toHigh);  // maps values from one range to another
      //Serial.println(motor_power);
      analogWrite(ENA, motor_power);
      break;

    case 2: // when var == 2 do this
      case_description = "Motor Stopped ";
      breakStop();
      break;

    case 3: // when var == 3 do this
      case_description = "Motor reverse ";
      goBackwards();
      value = analogRead(POT);                                    // reads the value from the pot and saves to a variable for re-mapping
      motor_power = map(value, fromLow, fromHigh, toLow, toHigh);  // maps values from one range to another
      //Serial.println(motor_power);
      analogWrite(ENA, motor_power);
      break;
      
    case 4: // when var == 3 do this
      case_description = "Motor Stopped ";
      breakStop();
      break;

    default:
      // it should not be in this state so we will flash the LED pin as a way of error checking
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for half a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(500);                       // wait for half a second
      break;
  }
  if (!digitalRead(BUTTON) && button_released) { // (! means not) (&& means and).
    //Entered if stament if button has been pressed and button has been released then since last pressed
    time_since_last_pressed = (millis() - last_time_pressed);
    last_time_pressed = millis();
    Serial.println(String(case_description + ", Last speed = " + String(motor_power) + ", Ran for  = " + time_since_last_pressed + " ms"));
    button_released = false;
    if (case_var < 4) {
      case_var++;   // Adds 1 to case_var
    }
    else {
      case_var = 1; // resets the case_var to the 1 and the procces repeats again
    }
    delay(50);// allows time for button to debouce.
  }

  if (digitalRead(BUTTON)) { // This is requied so that when the button is pressed it does not continually read as being pressed
    button_released = true;
    delay(50);// allows time for button to debouce.
  }
}

void goForwards() {  // void is used to define a function that does not return anything
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

void breakStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
