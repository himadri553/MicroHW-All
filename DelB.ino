#include <avr/io.h>
#include <util/delay.h>

#define LED PG5
#define POT PF0

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

// possible assembly equivalent
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 5          // LED connected to digital pin 5
#define POT_PIN A0         // Potentiometer connected to analog pin A0

; Initialize the program
.global main
main:
    ; Setup Port D for output (LED) and Port C for input (Potentiometer)
    ldi r16, 0xFF       ; Set DDRD to all output
    out DDRD, r16
    ldi r16, 0x00       ; Set DDRC to all input
    out DDRC, r16

    ; Setup ADC
    ldi r16, 0b11001111 ; Set ADC Control and Status Register A (ADCSRA)
                        ; Enable ADC, Enable ADC Interrupt, Prescaler = 128
    out ADCSRA, r16
    ldi r16, 0b00000000 ; Set ADC Multiplexer Selection Register (ADMUX)
                        ; Reference Voltage = AVCC, Left Adjust Result
    out ADMUX, r16

  // timer part may not be necessary

    ; Setup Timer1 for PWM
    ldi r16, (1 << COM1A1) | (1 << WGM11) | (1 << WGM10) ; Fast PWM, Clear OC1A on Compare Match
    out TCCR1A, r16
    ldi r16, (1 << WGM13) | (1 << WGM12) | (1 << CS11) ; Prescaler = 8
    out TCCR1B, r16
    ldi r16, 0xFF       ; Set OC1A (Pin 5) as output
    out DDRB, r16

    ; Setup Timer1 Compare Register A (TOP) for PWM frequency
    ldi r16, 156        ; PWM Frequency = 16MHz / (8 * (1 + 156)) = 10kHz
    out OCR1A, r16

    ; Enable global interrupts
    sei

; Main loop
loop:
    rcall read_potentiometer  ; Read potentiometer value
    out OCR1AL, r24            ; Set PWM duty cycle based on potentiometer value
    rjmp loop

; Subroutine to read potentiometer value
read_potentiometer:
    ; Start ADC conversion
    ldi r16, (1 << ADEN) | (1 << ADSC)
    out ADCSRA, r16

    ; Wait for conversion to complete
adc_wait:
    in r16, ADCSRA
    sbrc r16, ADSC
    rjmp adc_wait

    ; Read ADC result
    in r24, ADCL    ; Low byte
    in r25, ADCH    ; High byte

    ret
