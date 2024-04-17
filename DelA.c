/*DelA*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PIN PG5 

void setup() {
  // Set LED pin as output
  DDRG |= (1 << LED_PIN);
  
  // Set Timer0 for Fast PWM with a prescaler of 64
  TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0B1); // Fast PWM mode, non-inverting
  TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler 64
}

void mainLoop() {
  // Set duty cycle (50% for 2Hz blinking)
  OCR0B = 255 / 2;
  _delay_ms(500); // Delay for half period (500ms for 2Hz)
}

int main() {
  setup();
  while(1) {
    mainLoop();
  }
  return 0;
}
