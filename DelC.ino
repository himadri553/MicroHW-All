// vars
#include <LiquidCrystal.h>
#define trigPin A2 // orange
#define echoPin A1  // green
float signalTime; // time it takes for signal to get back
float final_distance;
float distanceCalcFactor = 0.0343 / 2; 
LiquidCrystal lcd(50, 46, 47, 49, 51, 53); // (rs, en, d4, d5, d6, d7)

float getDistance() {
  /* Get distance */
  digitalWrite(trigPin, LOW); // reset pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  signalTime = pulseIn(echoPin, HIGH); // get time for signal to get back 
  return distanceCalcFactor * signalTime;
}

void setup() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  // for sensor
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  final_distance = getDistance();
  
  /*Print Distance in Cm on LCD*/
  lcd.clear(); // refresh screen
  lcd.println(final_distance);
  lcd.print(" cm");
  delay(1000); // refresh time
}
