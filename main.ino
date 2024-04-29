  // backwards: RServo.write(180); 
  // forwards: RServo.write(-180); 
  // forwards: LServo.write(180); 
  // backwards: LServo.write(-180); 
  // Stop: LServo.write(90); 
  // Stop: RServo.write(90);
  // IR d2

  /*
    Digital Output: servos
    Digital Input: IR reciver
    Analog Output: LED??
    Analog Input: POT controls ??
    IR keeps sending some signal, regardless of if the remote is pressed or not (bad for interupt)

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

void setup() {
  Serial.begin(9600);
  RServo.attach(R_ServoPin);
  LServo.attach(L_ServoPin);
  IrReceiver.begin(IR_Reciver, ENABLE_LED_FEEDBACK);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
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
  /*get duration*/
  moveLength = analogRead(POT);
  Serial.println(moveLength);

  /*Change LED*/
  analogWrite(LED, moveLength/4.5);

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
