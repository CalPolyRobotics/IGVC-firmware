#include <avr/io.h>
#include <avr/interrupt.h>

#include "HallEffect.h"
#include "../../usart.h"

static int hallData = 0;

void initializeHallEffect() {
   
   TCCR4A = 0;
   TCCR4B = (1 << CS42);
   TIMSK4 = (1 << TOIE4);

   TCNT4H = 0;
   TCNT4L = 0;

   PCMSK1 = (1 << PCINT14);
   PCICR = 1 << PCIE1;

}

ISR(PCINT1_vect) {
   hallData = TCNT4L;
   hallData |= (TCNT4H << 8);
   TCNT4H = 0;
   TCNT4L = 0;
}

ISR(TIMER4_OVF_vect) {
   hallData = 0;
}

void getSpeed(unsigned char* data) {
   data[0] = (unsigned char)(hallData & 0xFF);
   data[1] = (unsigned char)(hallData >> 8);
}


