#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PIN         PB3     // PWM pin, corresponds to digital pin 11 on Arduino Uno

volatile uint8_t duty_cycle = 128; // Initial duty cycle, 50%

void setup_pwm() {
    // Set PWM pin (PB3) as output
    DDRB |= (1 << LED_PIN);

    // Set Timer/Counter1 for Fast PWM mode
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10); // No prescaling

    // Set Timer/Counter1 for 2 Hz frequency
    OCR1A = 15624; // (16000000 / (2 * 256)) - 1

    // Enable Timer/Counter1 overflow interrupt
    TIMSK1 |= (1 << TOIE1);
}

void mainLoop() {
    OCR0B = 20; // set duty cycle and compare register 
    TCCR0A = 0b10100011; // set fast mode
    TCCR0B = 0b00000001; // start PWM output    
}

int main() {
    setup_pwm();

    // Enable global interrupts
    sei();

    while (1) {
        // Main loop
    }

    return 0;
}

// Timer1 overflow interrupt service routine
ISR(TIMER1_OVF_vect) {
    // Toggle LED at 2 Hz
    duty_cycle = (duty_cycle == 0) ? 128 : 0;
    OCR1B = duty_cycle;
}
