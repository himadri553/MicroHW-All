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
  TCCR3A |= 1<<COM3C1 | 1<<WGM30;
  TCCR3B |= 1<<WGM32 | 1<<CS30;

  // Timer for speaker tone
  OCR4A = 0;
  OCR4C = 0;
  TCCR4A = 0;
  TCCR4B = 1<<WGM42 | 1<<CS40;

  EIMSK |= 1<<INT4;
  EICRB |= 1<<ISC41;
  sei();
}

void mainLoop() {

  PORTJ |= TRG;
  _delay_us(10);
  PORTJ &= ~TRG;

  while(!(PINJ & ECHO)) {
    duration++;
    if(duration >= 640000) {
      break;
    }
  } 

  // measure number of microseconds (approx) that the pulse lasts
  while(PINJ & ECHO) {
    elapsedTime++;
    _delay_ms(1);
    if(elapsedTime >= 640000) {
      break;
    }
  }

 if(mode) {
    // set pitch: shorter return should be higher pitch
    OCR4A = F_CPU / 5000 - elapsedTime/4 - 1;
    TIMSK4 |= 1<<OCIE4A;
    PORTE &= ~RED;
    
  }
  else {
    // set LED brightness: brighter when closer
    OCR3C = 255 - elapsedTime/64;
    if(elapsedTime/64 > 255) {
      OCR3C = 0;
    }
  }

  // delay to prevent interfering with the last pulse
  _delay_ms(100);
  elapsedTime = 0;
  duration = 0;
}

int main(void) {
  setupVars();
  while(1) {
    mainLoop();
  }
}

ISR(INT1_vect) {
  // Speaker to LED
  if(!mode) {
    // Stop Speaker
    TIMSK4 &= ~(1<<OCIE4A);
    mode = 0;
  }
  // LED to Speaker
  else {
    // Stop LED
    OCR3C = 0;
    mode = 1;
  }
}

// Time to manage speaker freq
ISR(TIMER4_COMPA_vect)
{
  PORTH ^= SPK;
}