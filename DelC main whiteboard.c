#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRG _BV(PJ0)
#define ECHO _BV(PJ1)
#define RED _BV(PE3)
#define BTN _BV(PE4)
#define SPK _BV(PH5)

#define MAX_WAIT 200

volatile unsigned char mode = 0;

unsigned long elapsedTime = 0;
unsigned long duration = 0;

void setupVars() {
    DDRJ |= TRG;
    DDRE |= RED;
    DDRH |= SPK;

    DDRJ &= ~ECHO;
    DDRE &= ~BTN;

    // PWM for LED
    OCR3C = 0;
    TCCR3A |= 1 << COM3C1 | 1 << WGM30;
    TCCR3B |= 1 << WGM32 | 1 << CS30;

    // Timer for speaker tone
    OCR4A = 0;
    OCR4C = 0;
    TCCR4A = 0;
    TCCR4B = 1 << WGM42 | 1 << CS40;

    EIMSK |= 1 << INT4; // Enable external interrupt 4
    EICRB |= 1 << ISC41 | 1 << ISC40; // Trigger INT4 on rising edge
    sei();
}

void mainLoop() {
    PORTJ |= TRG;
    _delay_us(10);
    PORTJ &= ~TRG;

    while (!(PINJ & ECHO)) {
        duration++;
        if (duration >= 640000) {
            break;
        }
    }

    while (PINJ & ECHO) {
        elapsedTime++;
        _delay_us(10);
        if (elapsedTime >= 640000) {
            break;
        }
    }

    if (mode) {
        // Set pitch: shorter return should be higher pitch
        OCR4A = F_CPU / 5000 - elapsedTime / 4 - 1;
        TIMSK4 |= 1 << OCIE4A;
        PORTE &= ~RED;
    } else {
        // Set LED brightness: brighter when closer
        OCR3C = 255 - (elapsedTime / 64); // Adjust based on distance
        if (OCR3C > 255) {
            OCR3C = 255;
        }
    }

    _delay_ms(100); // Delay to prevent interfering with the last pulse
    elapsedTime = 0;
    duration = 0;
}

int main(void) {
    setupVars();
    while (1) {
        mainLoop();
    }
}

ISR(INT4_vect) { // ISR for button press
    // Toggle mode between LED and speaker output
    mode = !mode;
    if (mode) {
        OCR3C = 0; // Turn off LED when switching to speaker output
    }
}

ISR(TIMER4_COMPA_vect) {
    PORTH ^= SPK; // Toggle speaker output
}
