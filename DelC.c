#define F_CPU 16000000UL  // Define CPU frequency
#include <avr/io.h>
#include <util/delay.h>

#define ADC_PIN 0          // ADC pin for potentiometer input
#define LED_PIN 6          // LED pin

void ADC_Init() {
    // Set reference voltage to AVcc and left adjust result
    ADMUX |= (1 << REFS0) | (1 << ADLAR);
    // Enable ADC, enable ADC interrupt, and set ADC prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t adc_channel) {
    // Select ADC channel
    ADMUX = (ADMUX & 0xF8) | (adc_channel & 0x07);
    // Start single conversion
    ADCSRA |= (1 << ADSC);
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    // Return ADC result
    return ADC;
}

void PWM_Init() {
    // Set LED pin as output
    DDRD |= (1 << LED_PIN);
    // Fast PWM mode, non-inverting
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    // Prescaler = 8
    TCCR0B |= (1 << CS01);
}

void PWM_Set(uint8_t duty_cycle) {
    // Set duty cycle (0-255)
    OCR0A = duty_cycle;
}

int main() {
    ADC_Init();  // Initialize ADC
    PWM_Init();  // Initialize PWM

    while (1) {
        // Read ADC value
        uint16_t adc_value = ADC_Read(ADC_PIN);
        // Map ADC value (0-1023) to PWM duty cycle (0-255)
        uint8_t duty_cycle = (adc_value >> 2);
        // Set PWM duty cycle
        PWM_Set(duty_cycle);
        // Delay for stability
        _delay_ms(10);
    }

    return 0;
}

