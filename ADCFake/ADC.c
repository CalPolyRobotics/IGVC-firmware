#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart.h"

void initADC(void);
void ADCStart(int i);

static int currDevice = 0;
static unsigned int ADCResults[8] = {0,0,0,0,0,0,0,0};

//Initialize ADC registers
void initADC(){
	ADCSRA = _BV(ADEN);
	ADMUX = _BV(REFS0)|(1);

	ADCSRB = 0;
	
   ADCStart(0);
}

//If the ADC isn't running, start it
void ADCStart(int port) {

		
	if(!(ADCSRA & _BV(ADSC))){
		ADCSRA &= ~((1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0));
		ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
		ADMUX &= ~((1 << MUX0)|(1 << MUX1)|(1 << MUX2)|(1 << MUX3));

		ADMUX |= port;
		
		ADCSRA |= _BV(ADIE);
		ADCSRA |= _BV(ADSC);
	}
}

unsigned int getADCResult(int i) {
   return ADCResults[i];
}

//Read the finished value of the ADC and store it
ISR(ADC_vect, ISR_NOBLOCK) {
   PORTD |= 0x8;
	int result = ADCL;
	result |= (ADCH << 8);
	
   result &= 0x3FF;

   ADCResults[currDevice] = result;

   ADCSRA &= ~(_BV(ADEN));
   currDevice++;
   
   if(currDevice > 5){
      currDevice = 0;
   }
   
   ADMUX &= ~(0xF);
   ADMUX |= currDevice;
   
   ADCSRA |= _BV(ADEN)|_BV(ADSC);
	

   PORTD &= ~(0x8);
}

