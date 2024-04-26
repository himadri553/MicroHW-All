#define LED_Pin 6 // define pin number for easy acess

void setup() {
  pinMode(LED_Pin,OUTPUT);
}

void loop() {
  digitalWrite(LED_Pin,HIGH);
  delay(250);
  digitalWrite(LED_Pin,LOW);
  delay(250);
}
