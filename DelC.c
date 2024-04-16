// This code is a shortened version of what Chat gave me. It said it combines the initialization of ADC and PWM directly in the main function and integrates the ADC reading and PWM setting within the main loop. 
// This simplification reduces the overall code size while retaining the functionality of controlling LED brightness with a potentiometer.

#define F_CPU 16000000UL  // Define CPU frequency      
// This line defines the CPU frequency as 16 MHz. This is necessary for proper timing functions like _delay_ms() to work accurately.

#include <avr/io.h> // This line includes the AVR I/O header file, which provides access to AVR-specific register definitions.
#include <util/delay.h> // This line includes the delay header file, which contains functions for creating time delays.

int main() {
    // Set reference voltage to AVcc and left adjust result
    ADMUX |= (1 << REFS0) | (1 << ADLAR); // This line configures the ADC Multiplexer Control Register (ADMUX) to set the reference voltage to AVcc and left-adjust the result. 
                                        // AVcc is the supply voltage to the AVR chip, and left-adjusting the result means that the most significant bits of the ADC conversion result will be placed in the ADCH register, making it easier to work with.
   
  // Enable ADC and set ADC prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // This line configures the ADC Control and Status Register A (ADCSRA) to enable the ADC and set the ADC clock prescaler to 128. 
                                                                       // This sets the ADC clock frequency to 125 kHz (16 MHz / 128), which is within the recommended range for accurate conversions.
    // Set LED pin as output
    DDRD |= (1 << 6); // This line sets pin 6 of port D (which corresponds to digital pin 6 on the Arduino Uno) as an output pin. This is where the LED will be connected.
    
  // Fast PWM mode, non-inverting, prescaler = 8
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // This line configures Timer/Counter Control Register A (TCCR0A) to set the Timer/Counter 0 (Timer 0) in Fast PWM mode with non-inverting mode. 
                                                          // This mode allows us to control the brightness of the LED using PWM.
    
  TCCR0B |= (1 << CS01); // This line configures Timer/Counter Control Register B (TCCR0B) to set the prescaler for Timer 0 to 8. This divides the system clock frequency by 8, providing the Timer 0 with a clock frequency of 2 MHz.

    while (1) {
        // Start single conversion
        ADCSRA |= (1 << ADSC); // This line starts a single ADC conversion by setting the ADC Start Conversion (ADSC) bit in the ADCSRA register.
        
      // Wait for conversion to complete
        while (ADCSRA & (1 << ADSC)); // This line waits for the ADC conversion to complete by polling the ADSC bit in the ADCSRA register. When the conversion is complete, this bit will be cleared automatically by the hardware.
        
      // Set PWM duty cycle (0-255) based on ADC value (0-1023)
        OCR0A = (ADCH >> 2); // This line sets the output compare register (OCR0A) of Timer 0 to control the PWM duty cycle. It uses the most significant 8 bits of the ADC result (ADCH), which are left-adjusted due to the configuration set earlier. 
                            // Since we're using 8-bit PWM, we right-shift ADCH by 2 bits to scale the ADC value from a range of 0-1023 to a range of 0-255, which corresponds to the duty cycle of the PWM signal.
        
      // Delay for stability
        _delay_ms(10);
    }

    return 0;
}
