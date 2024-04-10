// Del B
#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;
void PWM_Signnal(float input, int num_cycles, int signal_pin) {
  float duty_cycle;
  for (int j = 0; j < num_cycles; j++) {
    //convert custom number to duty cycle
    if (input >= 0 && input <= 10) {
      duty_cycle = ((input / 10) * 100); 
    } 

    // run PWM signal
    for (int i = 1; i < 100; i++) {
      if (duty_cycle >= i) {
        digitalWrite(signal_pin, HIGH);
      }
      else {
        digitalWrite(signal_pin, LOW);
      }
    }
  }
  Serial.println(duty_cycle);
}

void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // my PWM signal control
  Serial.println("PWM full then slow");
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  PWM_Signnal(10, 100, ENABLE); //enable on
  delay(2000); 
  PWM_Signnal(8, 100, ENABLE); // will not slow down, just shut off
  delay(2000);

  // analog write one to compare
  Serial.println("full then slow");
  analogWrite(ENABLE,255); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(1000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
}
   
