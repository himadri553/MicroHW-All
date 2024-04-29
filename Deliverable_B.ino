/* 
  corrected:
  - pin definitions 
  - changed potiometer to anlogRead

*/
#define RED_LED 3
#define Speaker 8
#define button 2
volatile int mode = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(Speaker, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), buttonPress, FALLING);
}

void loop() { // Based on mode, play tone on speaker
  digitalWrite(RED_LED, HIGH);
  int aval = analogRead(A0);
  if (mode) {
    tone(Speaker, 4978-(4*aval),1);
  }
  else {
    analogWrite(RED_LED, aval);
  }
}

void buttonPress() { // swtich modes at interupt, 
  if (mode) {
    noTone(Speaker);
    mode = 0;
  }
  else {
    analogWrite(RED_LED, 0);
    mode = 1;
  }
}
