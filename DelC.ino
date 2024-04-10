/*
  Del C:
  button(toggle) will turn LED on or off
  once the button is turned on, wait and turn servo on to push the button off
  if possible, use a counter to make the machine more "mad" and swtich up servo behavior
*/
#define buttonPin 2
#define LED_Pin 42

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    // switch is on
  }
  else { (switchState == LOW) 
    // switch is off
  }
  delay(1000);
}

