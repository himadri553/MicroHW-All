// Pin connected to LED
#define ledPin 44

void setup() {
  // Set the ledPin as an output
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void PWM_Signnal(float input) {
  //convert custom number to duty cycle
  float duty_cycle;
  if (input >= 0 && input <= 15) {
    duty_cycle = ((input / 15) * 255); // Convert input to percentage of 255
    Serial.println(duty_cycle);
  } else {
    Serial.println("Input number must be between 0 and 15");
  }

  // run PWM signal
  analogWrite(ledPin, duty_cycle);
}

void loop() {
  for (int i = 0; i < 15; i++) {
    PWM_Signnal(i);
    delay(1000);
  }
}
