/*
  DelB
  data sheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
*/

#define trigPin A2 // orange
#define echoPin A1  // green

// vars
float signalTime; // time it takes for signal to get back
float final_distance;
float distanceCalcFactor = 0.0343 / 2; // factor to calc distance (from datasheet? - sorta)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void trigger() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void loop() {
  /* Get distance */
  digitalWrite(trigPin, LOW); // reset pin
  trigger(); // send signal out
  signalTime = pulseIn(echoPin, HIGH); // get time for signal to get back 
  final_distance = distanceCalcFactor * signalTime;

  /* Output distance */
  Serial.println(final_distance);
  delay(1000); // so the loop chills
}
