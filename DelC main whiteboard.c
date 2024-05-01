/*
  corrected:
  - turn off speaker / LED on during main loop
  - mode switching works (button pull up)

  not fix:
  - sensor wont effect any thing
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRG _BV(PJ0) // d15 = PJ0
#define ECHO _BV(PJ1) // d14 = PJ1
#define RED _BV(PE5) // d3 = PE5
#define BTN _BV(PE4) // d2 = PE4
#define SPK _BV(PH5) // d8 = PH5

#define MAX_WAIT 200
volatile unsigned char mode = 0;
volatile long elapsedTime = 0;
volatile long duration = 0;

void setupVars() {
  // input and output setup
  DDRJ |= TRG;
  DDRE |= RED;
  DDRH |= SPK;
  DDRJ &= ~ECHO;
  DDRE &= ~BTN; // button pullup 
  PORTD |= BTN;

  // PWM for LED
  OCR3C = 0;
  TCCR3A |= 1 << COM3C1 | 1 << WGM30;
  TCCR3B |= 1 << WGM32 | 1 << CS30;
  
  // Timer for speaker tone
  OCR4A = 0;
  OCR4C = 0;
  TCCR4A = 0;
  TCCR4B = 1 << WGM42 | 1 << CS40;

  // enable inteript on int4 and set to falling edge. Set to global (good)
  EIMSK |= 1 << INT4;
  EICRB |= 1 << ISC41;
  sei();
}

void mainLoop() {
  // send out signal
  PORTJ |= TRG;
  _delay_us(10);
  PORTJ &= ~TRG;

  // counter until ??
  while(!(PINJ & ECHO)) {
    duration++;
    if(duration >= 640000) {
      break;
    }
  } 

  // counter until ?? 
  while(PINJ & ECHO) {
    elapsedTime++;
    _delay_ms(1);
    if(elapsedTime >= 640000) {
      break;
    }
  }

  // based on elapsedTime
  if (mode) { /*Speaker Mode*/
    OCR3C = 0; // stop LED
    OCR4A = F_CPU / (5000 - elapsedTime / 4) - 1;
    TIMSK4 |= 1 << OCIE4A;
    PORTE &= ~RED; // also stop LED? 
  }
  else { /*LED mode*/
    TIMSK4 &= ~(1 << OCIE4A); // turn off speaker
    OCR3C = 255 - (elapsedTime / 64); // turn on LED
    if (elapsedTime >= MAX_WAIT) { // Turn off LED if distance exceeds MAX_WAIT
      OCR3C = 0;
    }
    if (OCR3C > 255) {
      OCR3C = 255;
    }
  }

  // delay to prevent interfering with the last pulse
  _delay_ms(100);
  elapsedTime = 0;
  duration = 0;
}

int main(void) {
  setupVars();
  while (1) {
    mainLoop();
  }
}

ISR(INT4_vect) { // just swtiches Mode
  // Speaker to LED
  if (mode) {
    mode = 0;
  }
  // LED to Speaker
  else {
    mode = 1;
  }
}

// Time to manage speaker freq
ISR(TIMER4_COMPA_vect) {
  PORTH ^= SPK;
}
