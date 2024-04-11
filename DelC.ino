/*
  Del C:
  button(toggle) will turn LED on or off
  once the button is turned on, wait and turn servo on to push the button off
  if possible, use a counter to make the machine more "mad" and swtich up servo behavior
*/
#include <Servo.h>
Servo servo;
#define buttonPin 2
#define LED_Pin 42
#define servoPin 23
int ledState = LOW;
int madState = 1;
bool mad_trigger = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;
int angle = 10;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_Pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), initial_buttonISR, FALLING);
  Serial.begin(9600);
  servo.attach(servoPin);
}

void loop() {
  // check if led is on, then get mad
  if (ledState == HIGH) {
    mad_trigger = true;
  }
  
  if (mad_trigger == true) {
    // select madstate
    switch (madState) { // its not swtiching!!!
      case 1:
        madState1();
        Serial.println("madState1");
        break;
      case 2:
        madState2();
        break;
      case 3:
        madState3();
        break;
    }
    // increment madState
    madState = madState + 1;
    if (madState == 3) {
      madState = 1;
    }
    // cool off after
    mad_trigger = false;
  }
}

void initial_buttonISR() {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) { // check debounce
    // toggle led
    ledState = !ledState;
    digitalWrite(LED_Pin, ledState);
  }
}
// servo actions when mad, will not be mad after
void madState1() { // somewhere here ig, after the led is turned off and 
  delay(1000);
  servo.write(0); 
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
}

void madState2() {
  delay(1500);
  servo.write(0); 
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
}

void madState3() {
  delay(2000);
  servo.write(0); 
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
}

