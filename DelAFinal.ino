/* DEL A
  PWM_Signnal: takes input(brightness) and number of cycles
  input (out of 15) is converted to a percentage which is then the duty cycle
  duty cycle: the percentage of the cycle that is on, rest is off
*/
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
  }
}

void loop() {
  for (int i = 0; i < 15; i++) {
    PWM_Signnal(i, 50);
  }
}
