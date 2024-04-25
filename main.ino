  // backwards: RServo.write(180); 
  // forwards: RServo.write(-180); 
  // forwards: LServo.write(180); 
  // backwards: LServo.write(-180); 
  // Stop: LServo.write(90); 
  // Stop: RServo.write(90);
#include <Servo.h>
Servo RServo;
Servo LServo;
#define R_ServoPin 44
#define L_ServoPin 45

void setup() {
  Serial.begin(9600);
  RServo.attach(R_ServoPin);
  LServo.attach(L_ServoPin);
}

/*All movement functions: Must have a delay after otherwise it wont stop!*/
void forwards(int duration) {
  LServo.write(180); 
  RServo.write(-180);
  delay(duration);
  LServo.write(90); 
  RServo.write(90);
}

void backwards(int duration) {
  LServo.write(-180); 
  RServo.write(180);
  delay(duration);
  LServo.write(90); 
  RServo.write(90);
}

void turnLeft(int duration) {
  LServo.write(180); 
  RServo.write(180);
  delay(duration);
  LServo.write(90); 
  RServo.write(90);
}

void turnRight(int duration) {
  LServo.write(-180); 
  RServo.write(-180);
  delay(duration);
  LServo.write(90); 
  RServo.write(90);
}

void loop() {
  forwards(2000);
  turnRight(2000);
  backwards(2000);
  turnLeft(2000);
  delay(2000);
}
