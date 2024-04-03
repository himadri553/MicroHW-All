// include the library code:
#include <LiquidCrystal.h>

// vars
#define trigPin A2 // orange
#define echoPin A1  // green
float signalTime; // time it takes for signal to get back
float final_distance;
float distanceCalcFactor = 0.0343 / 2; 
LiquidCrystal lcd(50, 46, 47, 49, 51, 53);

void trigger() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void setup() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  // for sensor
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  /* Get distance */
  digitalWrite(trigPin, LOW); // reset pin
  trigger(); // send signal out
  signalTime = pulseIn(echoPin, HIGH); // get time for signal to get back 
  final_distance = distanceCalcFactor * signalTime;
  
  /*Print Distance in Cm on LCD*/
  lcd.clear(); // refresh screen
  lcd.println("Distance: ");
  lcd.println(final_distance);
  lcd.print("cm");
  delay(1000); // refresh time
}
