// DelA complete
#define pot A11

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(pot));
}
