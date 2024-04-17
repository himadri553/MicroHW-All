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
#define POT PF0 // green: A0
int DelState = 0; // 0: B, 1: C

void setup() {
  DDRG |= (1 << LED); // Set LED pin to output (pin 4)
  DDRD &= ~(1<<button); // dpin 51 (pullup)
  PORTD |= (1<<button);
  DDRF &= ~(1 << POT); // Potentiometer setup
  PORTF &= ~(1 << POT);

  // enable interrupt
  EIMSK |= (1<<INT2);
  EICRA |= (1<<ISC20);
  sei();

  // Configure ADC
  ADMUX = (1 << REFS0); // Set reference voltage to AVcc
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128
}

void DelB () {
  // Cycle through five levels of brightness (0%, 25%, 50%, 75%, 100%)
  for (int i = 0; i <= 100; i += 25) {
    OCR0B = (i * 255) / 100; // Map percentage to PWM value
    TCCR0A = 0b10100011; // Set fast PWM mode, non-inverting mode
    TCCR0B = 0b00000001; // Start PWM output
    _delay_ms(500); // Pause for 500 milliseconds
  }
}

void DelC() {
  // Start ADC conversion and wait for it to complete 
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));

  // Get ADC value 
  unsigned int adcValue = ADC;

  // light LED up
  OCR0B = ADC/10; // Map percentage to PWM value
  TCCR0A = 0b10100011; // Set fast PWM mode, non-inverting mode
  TCCR0B = 0b00000001; // Start PWM output

  // Delay for stability 
  _delay_ms(10);
}

void mainLoop() {
  // check which Del to be in, and the run that Del
  if (DelState == 0) {
    // run delB
    DelB();
  }
  else {
    // run delC
    DelC();
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
