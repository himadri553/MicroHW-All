  // backwards: RServo.write(180); 
  // forwards: RServo.write(-180); 
  // forwards: LServo.write(180); 
  // backwards: LServo.write(-180); 
  // Stop: LServo.write(90); 
  // Stop: RServo.write(90);
  // IR d46
#include <Servo.h>
#include <IRremote.hpp> 
Servo RServo;
Servo LServo;
#define R_ServoPin 44
#define L_ServoPin 45
#define IR_Reciver 46
int debouceFactor = 50;
int lastButtonPress = 0;

void setup() {
  Serial.begin(9600);
  RServo.attach(R_ServoPin);
  LServo.attach(L_ServoPin);
  IrReceiver.begin(IR_Reciver, ENABLE_LED_FEEDBACK);
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
  if (IrReceiver.decode()) { // check for button press
    if (millis() >= (lastButtonPress + debouceFactor)) { // check for debounce
      lastButtonPress = millis();
      switch (IrReceiver.decodedIRData.command) {
        case 0x46: //forwards
          forwards(1000);
          delay(1000);
        break;

        case 0x15: // down
          backwards(1000);
          delay(1000);
        break;

        case 0x44:// left
          turnLeft(1000);
          delay(1000);
        break;

        case 0x43: // right
          turnRight(1000);
          delay(1000);
        break;
      }
    }
  }
}
