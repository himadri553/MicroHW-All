// Del B
#define ENABLE 5 // red
#define DIRA 3 // blue
#define DIRB 4 // yellow

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
  /*My pwm signal*/
  Serial.println("Custom PWM control");
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  PWM_Signnal(10, 100, ENABLE); //enable on
  delay(2000); 
  PWM_Signnal(8, 100, ENABLE); // will not slow down, just shut off
  delay(2000);

  /*analog write*/ 
  Serial.println("analogWrite control");
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  for (int i = 0; i < 255; i++) {
    analogWrite(ENABLE, i); //enable on
    delay(40);
  }
  analogWrite(ENABLE, 0);
  delay(2000);
}
   
