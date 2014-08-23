#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"

static int SPIState = 0;
static int value;

void initSPI() {

   SPCR = (1 << SPIE)|(1 << SPE);

}

void SPIReset() {
   SPIState = 0;
}

ISR(SPI_STC_vect) {
   PORTD |= 0x4;
   if(SPIState == 0) {
      value = getADCResult(SPDR);
      SPDR = value >> 8;
      SPIState++;
   } else if(SPIState == 1) {
      SPDR = value & 0xFF;
      SPIState++;
   } else {
      SPIState = 0;
   }
   PORTD &= ~(0x4);
}
