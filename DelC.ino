const int switchPin = 2;

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    // switch is on
  }
  else
  { (switchState == LOW) 
    // switch is off
  }
  delay(1000);
}

