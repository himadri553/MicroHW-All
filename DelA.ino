// Pin connected to LED
#define ledPin 44

void setup() {
  // Set the ledPin as an output
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void PWM_Signnal(float input, int num_cycles) {
  for (int j = 0; j < num_cycles; j++) {
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
      }
      else {
        digitalWrite(ledPin, LOW);
      }
    }
    delay(100); // just for testing
  }
}

void loop() {
  PWM_Signnal(1, 100);
}
