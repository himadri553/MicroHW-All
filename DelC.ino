// Define the pin the switch is connected to
const int switchPin = 2; // Change this to match the pin you've connected the switch to

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the state of the switch
  int switchState = digitalRead(switchPin);

  // Check if the switch is turned on
  if (switchState == HIGH) {
    // switch is on
  }
  else
  { (switchState == LOW) 
    // switch is off
  }
  delay(1000);
}

