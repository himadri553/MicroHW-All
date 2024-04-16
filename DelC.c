#define F_CPU 16000000UL  // Define CPU frequency                                    // This version combines the initialization of ADC and PWM directly in the main function and integrates the ADC reading and PWM setting within the main loop. 
                                                                                    // This simplification reduces the overall code size while retaining the functionality of controlling LED brightness with a potentiometer.
#include <avr/io.h>
#include <util/delay.h>

int main() {
    // Set reference voltage to AVcc and left adjust result
    ADMUX |= (1 << REFS0) | (1 << ADLAR);
    // Enable ADC and set ADC prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Set LED pin as output
    DDRD |= (1 << 6);
    // Fast PWM mode, non-inverting, prescaler = 8
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS01);

    while (1) {
        // Start single conversion
        ADCSRA |= (1 << ADSC);
        // Wait for conversion to complete
        while (ADCSRA & (1 << ADSC));
        // Set PWM duty cycle (0-255) based on ADC value (0-1023)
        OCR0A = (ADCH >> 2);
        // Delay for stability
        _delay_ms(10);
    }

    return 0;
}
