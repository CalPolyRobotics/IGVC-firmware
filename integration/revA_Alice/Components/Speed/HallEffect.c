/**
 * HallEffect.c
 * Written by Gerik Kubiak.
 *
 * Code to recieve data from the Hall Effect
 * sensor. Used to determine speed.
**/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "HallEffect.h"
#include "../../usart.h"

static int hallData = 0;

/*
 * Initialize the timers and pin change interrups
 * used by the Hall Effect sensor.
 */
void initializeHallEffect() {
   
   TCCR4A = 0;
   TCCR4B = (1 << CS42);
   TIMSK4 = (1 << TOIE4);

   TCNT4H = 0;
   TCNT4L = 0;

   PCMSK1 = (1 << PCINT14);
   PCICR = 1 << PCIE1;

}

/*
 * Interrupt used to read the Hall Effect sensor.
 * Reads and resets the timer on every Hall Effect edge.
 */
ISR(PCINT1_vect) {
   hallData = TCNT4L;
   hallData |= (TCNT4H << 8);
   TCNT4H = 0;
   TCNT4L = 0;
}

/*
 * On overflow set hallData to 0.
 */
ISR(TIMER4_OVF_vect) {
   hallData = 0;
}

/*
 * Returns the number of clock ticks for the latests hall effect read.
 *
 * unsigned char* data: A pointer where to put the hall effect data.
 */
void getSpeed(unsigned char* data) {
   data[0] = (unsigned char)(hallData & 0xFF);
   data[1] = (unsigned char)(hallData >> 8);
}


