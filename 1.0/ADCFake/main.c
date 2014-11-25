#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"
#include "SPI.h"
#include "usart.h"

int main() {

   DDRB = (1 << PB4);
   DDRD |= (1 << PD2)|(1 << PD3);

   sei();

   initUSART();
   initSPI();
   initADC();

   while(1){
      if(PINB & (1 << PB2)) {
         SPIReset();
      }
   }
}
