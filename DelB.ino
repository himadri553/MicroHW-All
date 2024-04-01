/*
  DelB
  data sheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

  doesnt work - just printing 0, does not change distance
*/

#define trigPin 9
#define echoPin 11

// vars
int triggerTime = 10;
int signalTime; // time it takes for signal to get back
int final_distance;
int distanceCalcFactor = 0.034 / 2; // factor to calc distance (from datasheet - sorta)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void trigger(int triggerTime_main) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(triggerTime_main);
  digitalWrite(trigPin, LOW);
}

void loop() {
  /* Get distance */
  digitalWrite(trigPin, LOW); // reset pin
  trigger(triggerTime); // send signal out
  signalTime = pulseIn(echoPin, HIGH); // get time for signal to get back 
  final_distance = distanceCalcFactor * signalTime;

  /* Output distance */
  Serial.println(final_distance);
  delay(1000); // so the loop chills
}
