/*
  DelD:
  LED: 4 blue
  Button: 6 yellow
  Pot: 7 green
  Set up an interrupt 
  that will swap between B and C above when the button is pressed
*/
#include <avr/interrupt.h>
#define LED 5 // AVR pin eq
#define button 6 // yellow
#define Pot 7 // green

void setup() {
  // Set LED pin to output (pin 4)
  DDRG |= (1 << LED);
  
}

void mainLoop() {
  OCR0B = 20; // set duty cycle and compare register 
  TCCR0A = 0b10100011; // set fast mode
  TCCR0B = 0b00000001; // start PWM output
}

int main(void) {
  setup();
  while(1){
    mainLoop();
  }

  return 0;
}
