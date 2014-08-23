//FNR controller functions
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FNR.h"

#define setABit(x) \
PORTA |= (1 << (x));

#define clearABit(x) \
PORTA &= ~(1 << (x));

void FNRForward(void);
void FNRReverse(void);
void FNRNeutral(void);


void FNRForward(){
	clearABit(1);
	while((PORTA & 0x2) != 0){
		clearABit(1);
		vTaskDelay(1);
	}
	setABit(0);

	//PORTL &= ~0x30;
}

void FNRReverse(){
	clearABit(0);
	while((PORTA & 0x1) != 0){
		clearABit(0);
		vTaskDelay(1);
	}
	setABit(1);

	//PORTL |= 0x30;
}

void FNRNeutral(){
	clearABit(0);
	clearABit(1);
	while((PORTA & 0x3) != 0){
		clearABit(0);
		clearABit(1);
		vTaskDelay(1);
	}
	//PORTL &= ~0x30;
}

//set the FNR controller, inputs are either -1, 0, or 1.
char setFNR(char FNR) {
   //dummy function, nothing happens
   //return success
	if(FNR == 0){
		FNRNeutral();
	} else if(FNR == 1){
		FNRForward();
	} else if(FNR == -1){
		FNRReverse();
	}

   return 1;
}

//get the current FNR state. Function follows same format for consistancy
char getFNR(char *sensorResponse) {
   if((PORTA & 1) && (PORTA & 2)) {
      clearABit(1);
      clearABit(0);
      sensorResponse[0] = 0;;
   } else if(PORTA & 1) {
      sensorResponse[0] = 1;
   } else if(PORTA & 2) {
      sensorResponse[0] = -1;
   } else {
      sensorResponse[0] = 0;
   }
   //return success
   return 1;
}
