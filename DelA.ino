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
    duty_cycle = ((input / 15) * 100); 
    Serial.println(duty_cycle);
  } 

  // run PWM signal
  for (int i = 1; i < 100; i++) {
    if (duty_cycle >= i) {
      digitalWrite(ledPin, HIGH);
      delayMicroseconds(duty_cycle);
    }
    else {
      digitalWrite(ledPin, LOW);
      delayMicroseconds(duty_cycle);
    }
  }
}

void loop() {
  PWM_Signnal(0);
}
