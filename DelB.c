/*DEL B*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LED PG5 // blue: dpin 4

void setup() {
  DDRG |= (1<<LED); // setup led
}

void mainLoop() {
  
}

int main() {
  setup();
  while(1){
    mainLoop();
  }
}
