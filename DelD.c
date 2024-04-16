/*
  DelD:
  Set up an interrupt 
  that will swap between B and C above when the button is pressed
*/
#include <avr/interrupt.h>
#define LED 5 // blue
#define button 6 // yellow
#define Pot 7 // green

void setup() {
  // Set LED pin to output (pin 5)
  /*
  Tried both DDRE and DDRG
  DDRE |= 0b00100000; 
  */
  DDRG |= (1 << LED);
  
}

void mainLoop() {
  OCR0B = 64; // set duty cycle and compare register 
  TCCR0A = 0b10100011; // set fast mode
  TCCR0B = 0b00000001; // start PWM output
  
  // PORTE |= (1 << LED);
}

int main(void) {
  setup();
  while(1){
    mainLoop();
  }

  return 0;
}
