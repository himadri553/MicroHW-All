/*
  corrected: 
  - pin definitons
  - delay value by using:
    freq = 1 / cycle length (seconds), and solving for delay value given freq = 5Hz. 
    Led is on for only half a cycle, so delay = cycle length / 2. Then converted into ms
*/
#define LED_Pin 5 // define pin number for easy acess

void setup() {
  pinMode(LED_Pin, OUTPUT);
}

void loop() {
  digitalWrite(LED_Pin, HIGH);
  delay(100);
  digitalWrite(LED_Pin, LOW);
  delay(100);
}
