/*DEL C*/
#include <avr/io.h>
#include <util/delay.h>

#define LED PG5
#define POT PF0

#define F_CPU 16000000UL  // Define CPU frequency 16MHz

void setup() {
  DDRG |= (1 << LED); // LED setup
  DDRF &= ~(1 << POT); // Potentiometer setup
  PORTF &= ~(1 << POT);

  // Configure ADC
  ADMUX = (1 << REFS0); // Set reference voltage to AVcc
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128
}

void mainLoop() {
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

int main() {
  setup();
  while (1) {
    mainLoop();
  }
  return 0;
}
