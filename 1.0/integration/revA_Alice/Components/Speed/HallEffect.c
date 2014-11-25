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

static unsigned int hallData = 0;

//If the timer overflows the next value is not useful. Throw it out.
static char trashData = 0;

static int hallEffectTicks = 0;

/*
 * Initialize the timers and pin change interrups
 * used by the Hall Effect sensor.
 */
void initializeHallEffect() {
   
   TCCR4A = 0;
   TCCR4B = (1 << CS42)|(1 << CS40);
   OCR4A = 0xFFFF;
   TIMSK4 = (1 << OCIE4A)|(1 << TOIE4);
   //TIMSK4 = (1 << TOIE4);

   TCNT4H = 0;
   TCNT4L = 0;

   //PCMSK1 = 0xFF;
   PCMSK1 = (1 << PCINT14);
   PCICR = 1 << PCIE1;
}

/*
 * Interrupt used to read the Hall Effect sensor.
 * Reads and resets the timer on every Hall Effect edge.
 */
ISR(PCINT1_vect) {
   unsigned int data;


   if(trashData == 0) {

      hallEffectTicks++;
      
      data = TCNT4L;
      data |= (TCNT4H << 8);

     
      //Jitter from the sensor can cause false edges. Mark as bad
      if(data > 100) {
         hallData = data;
         if(data < 0x3FFF) {
            OCR4A = data << 1;
         } else {
            OCR4A = 0xFFFF;
         } 
      }

   } else {
      trashData = 0;
   }

   TCNT4H = 0;
   TCNT4L = 0;
}

/*
 * On overflow set hallData to 0.
 */
ISR(TIMER4_OVF_vect) {
   hallData = 0;
   trashData = 1;
   OCR4A = 0xFFFF;
}

/*
 * Used for dynamic overflow
 */
ISR(TIMER4_COMPA_vect) {
   hallData = 0;
   trashData = 1;
   OCR4A = 0xFFFF;
   TCNT4H = 0;
   TCNT4L = 0;
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

/*
 * Returns the number of hall effect ticks since the last read.
 *
 * unsigned char* data: A pointer where to put the hall effect ticks.
 */
void getTicks(unsigned char* data) {
   data[0] = (unsigned char)(hallEffectTicks & 0xFF);
   data[1] = (unsigned char)(hallEffectTicks >> 8);
   
   hallEffectTicks = 0;
}


