/*
  DelD:
  LED: 4 blue
  Button: 6 yellow
  Pot: 7 green
  Set up an interrupt 
  that will swap between B and C above when the button is pressed
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED PG5 // blue: dpin 4
#define button PD2 // yellow: dpin 19, INT2 
#define Pot PINH4 // green: dpin 7
int DelState = 0; // 0: B, 1: C

void setup() {
  DDRG |= (1 << LED); // Set LED pin to output (pin 4)
  DDRD &= ~(1<<button); // dpin 51 (pullup)
  PORTD |= (1<<button);

  // enable interrupt
  EIMSK |= (1<<INT2);
  EICRA |= (1<<ISC20);
  sei();
}

void mainLoop() {
  // check which Del to be in, and the run that Del
  if (DelState == 1) {
    // run delB
    PORTG |= (1<<LED);
  }
  else {
    // run delC
    PORTG &= ~(1 << LED);
  }
}

int main() {
  setup();
  while(1){
    mainLoop();
  }
}

ISR (INT2_vect) {
  DelState = !DelState;
}
