/*Del B*/
#include <avr/io.h>
#include <util/delay.h>

#define LED PG5 // Blue LED connected to pin 13 (PG5)

void setup() {
  DDRG |= (1 << LED); // Set LED pin to output
}

void mainLoop() {
  // Cycle through five levels of brightness (0%, 25%, 50%, 75%, 100%)
  for (int i = 0; i <= 100; i += 25) {
    OCR0B = (i * 255) / 100; // Map percentage to PWM value
    TCCR0A = 0b10100011; // Set fast PWM mode, non-inverting mode
    TCCR0B = 0b00000001; // Start PWM output
    _delay_ms(500); // Pause for 500 milliseconds
  }
}

int main() {
  setup();
  while (1) {
    mainLoop();
  }
  return 0;
}
