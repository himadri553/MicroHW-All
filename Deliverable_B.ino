/* 
  corrected:
  - pin definitions 
  - changed potiometer to anlogRead
  - added debounce for button press
  - removed inital HIGH output for LED in main loop
  - removed all additional code in interupt function, so that interupt is only responisble for swtiching modes

*/
#define RED_LED 3
#define Speaker 8
#define button 2
#define POT A0
volatile int mode = 0;
unsigned long debounceFactor = 50;
unsigned long lastTime = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(Speaker, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), buttonPress, FALLING);
  Serial.begin(9600);
}

void loop() { // Based on mode, play tone on speaker
  int aval = analogRead(POT);
  if (mode) { // speaker play mode 
    tone(Speaker, 4978-(4*aval), 1);
    analogWrite(RED_LED, LOW); // wont shut off
  }
  else { // LED control mode
    analogWrite(RED_LED, aval);
    noTone(Speaker);
  }
}

void buttonPress() { // swtich modes at interupt, 
  unsigned long currentTime = millis(); // added debounce 
  if ((currentTime - lastTime) > debounceFactor) {
    lastTime = currentTime;
    if (mode) {
      mode = 0;
    }
    else {
      mode = 1;
    }
  }
}
