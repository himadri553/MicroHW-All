/*
  Del C:
  button(toggle) will turn LED on or off
  once the button is turned on, wait and turn servo on to push the button off
  if possible, use a counter to make the machine more "mad" and swtich up servo behavior
*/
#define buttonPin 2
#define LED_Pin 42
int ledState = LOW;
int madState = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // vars
  int switchState = digitalRead(buttonPin);

  // when button is pressed...
  if (switchState == LOW) {
    // switch light colors
    ledState = !ledState;
    digitalWrite(LED_Pin, ledState);

    // get mad
    switch (madState) {
      case 1:
        madState1();
        break;
      case 2:
        madState2();
        break;
      case 3:
        madState3();
        break;
    }

    // next mad state
    madState = madState + 1;
    if (madState == 3) {
      madState = 1;
    }
  }

}

void madState1() {
  
}

