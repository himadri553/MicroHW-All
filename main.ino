/*
  Himadri Saha, Tejas Patil, Daniel Diep, Ashwin Srinivasan
  EECE.3170
  Final Project: Remote controlled car with distance control
*/
#include <Servo.h>
#include <IRremote.hpp>
#include <avr/interrupt.h>
Servo RServo;
Servo LServo;
#define R_ServoPin 11 // PWM
#define L_ServoPin 12 // PWM
#define IR_Reciver 2 // Any digital Pin with interupt 
#define POT A0 // analog pin
#define LED 6
int debouceFactor = 100;
int lastButtonPress = 0;
int moveLength;

/* Set all pins here to corresponding input/output */
void setup() {
  Serial.begin(9600);
  RServo.attach(R_ServoPin);
  LServo.attach(L_ServoPin);
  IrReceiver.begin(IR_Reciver, ENABLE_LED_FEEDBACK);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
}

/*Each diricitonal movement is split up with a variable time duration. All movement functions: Must have a delay after otherwise it wont stop!*/
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
  /*get duration*/
  moveLength = analogRead(POT) + 50;
  Serial.println(moveLength);

  /*Change LED*/
  analogWrite(LED, (moveLength - 50) / 4.5);

  /*Control movement*/
  if (IrReceiver.decode()) { // check for button press
    if (millis() >= (lastButtonPress + debouceFactor)) { // check for debounce
      lastButtonPress = millis();

      switch (IrReceiver.decodedIRData.command) { // control movement
        case 0x46: //forwards
          forwards(moveLength);
          delay(moveLength);
        break;

        case 0x15: // down
          backwards(moveLength);
          delay(moveLength);
        break;

        case 0x44:// left
          turnRight(moveLength);
          delay(moveLength);
        break;

        case 0x43: // right
          turnLeft(moveLength);
          delay(moveLength);
        break;
      }
      IrReceiver.resume();
    }
  }
}
