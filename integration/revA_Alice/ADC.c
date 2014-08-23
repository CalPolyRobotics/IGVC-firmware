#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

typedef struct ADCDevice {
	int port;
	int options;
	void* parameters;
	ADCHandler handler;
} ADCDevice;

void initADC(void);
void ADCStart(ADCDevice* nextDevice);

static xSemaphoreHandle* adcSemaphore;
static ADCDevice devices[16];
static int currDevice = 0;
static int ADCinitialized = 0;

//Initialize ADC registers
void initADC(){
   //Uncomment when ADC is fixed
	/*ADCSRA = _BV(ADEN);
	ADMUX = _BV(REFS0)|(1);

	ADCSRB = (1 << MUX5);*/
	
}

//If the ADC isn't running, start it
void ADCStart(ADCDevice* nextDevice) {

		
	if(!(ADCSRA & _BV(ADSC))){
		ADCSRA &= ~((1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0));
		switch(nextDevice->options & ADC_OPT_PRECISION_MASK){
		case ADC_OPT_PRECISION_HIGH:
			ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
			break;
		case ADC_OPT_PRECISION_MED_HIGH:
			ADCSRA |= (1 << ADPS2)|(1 << ADPS0);
			break;
		case ADC_OPT_PRECISION_MED:
			ADCSRA |= (1 << ADPS1)|(1 << ADPS0);
			break;
		case ADC_OPT_PRECISION_LOW:
			break;
		}
		ADMUX &= ~((1 << MUX0)|(1 << MUX1)|(1 << MUX2)|(1 << MUX3));
		if(nextDevice->port < 8){
			ADCSRB &= ~(1 << MUX5);
			ADMUX |= nextDevice->port;
		} else {
			ADCSRB |= (1 << MUX5);
			ADMUX |= nextDevice->port - 8;
		}
		
		ADCSRA |= _BV(ADIE);
		ADCSRA |= _BV(ADSC);
	}
}

//Read the finished value of the ADC and store it
ISR(ADC_vect) {
	int result = ADCL;
	result |= (ADCH << 8);
	
   result &= 0x3FF;

   ADCSRA &= ~(_BV(ADIE));
	
	ADCHandler handler = devices[currDevice].handler;
	void *parameters = devices[currDevice].parameters;
	
	handler(result,parameters);
	
	xSemaphoreGiveFromISR(adcSemaphore,0);
}

void vTaskADC(void *parameters){
	
	int i;

	for(i = 0;i < 16; i++){
		devices[i].port = -1;
	}

	initADC();

	vSemaphoreCreateBinary(adcSemaphore);
	
	ADCinitialized = 1;
	while(devices[0].port == -1){
		vTaskDelay(10);
	}
	
   //ADC currently broken. Using ADC on separate Arduino
   /*currDevice = 0;

	while(1){
		ADCStart(&devices[currDevice]);
		xSemaphoreTake(adcSemaphore,portMAX_DELAY);
		currDevice++;
		if(currDevice >= 16 || devices[currDevice].port == -1){
			currDevice = 0;
		}
	}*/
   
   unsigned int adcResult;

   currDevice = 0;
   while(1) {
      enableSS();
      SPIsendByteNoSS(devices[currDevice].port & 0xFF);
      adcResult = SPIsendByteNoSS(0) << 8;
      adcResult |= SPIsendByteNoSS(0) & 0xFF;
      disableSS();
      devices[currDevice].handler(adcResult, devices[currDevice].parameters);
      currDevice++;
      if(currDevice > 6 || devices[currDevice].port == -1) currDevice = 0;
      vTaskDelay(1);
   }
      
   
}

void addADCDevice(int port,int options,ADCHandler handler,void* parameters){
	int i;
	
	//Creating a device before all the structures are initialized
	//could lead to race conditions.
	while(ADCinitialized == 0) vTaskDelay(3);

	for(i = 0; i < 16 && devices[i].port != -1; i++)
	;
	
	if(port < 8){
		DIDR0 &= ~(1 << port);
	} else {
		DIDR2 &= ~(1 << (port - 8));
	}

	if(devices[i].port == -1){
		devices[i].port = port;
		devices[i].options = options;
		devices[i].handler = handler;
		devices[i].parameters = parameters;
	}
}
