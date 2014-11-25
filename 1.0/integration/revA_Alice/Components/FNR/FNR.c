/**
 * FNR.c
 * Written by Gerik Kubiak.
 *
 * Contains functions to control the state of the FNR.
**/

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

/*
 * Sets the FNR to forward.
 * Not sure is checking PORTA is useful, but it at least
 * provides a delay for the solenoids to switch.
 */
void FNRForward(){
	clearABit(1);
	while((PORTA & 0x2) != 0){
		clearABit(1);
		vTaskDelay(1);
	}
	setABit(0);
}

/*
 * Sets the FNR to reverse.
 */
void FNRReverse(){
	clearABit(0);
	while((PORTA & 0x1) != 0){
		clearABit(0);
		vTaskDelay(1);
	}
	setABit(1);
}

/*
 * Sets the FNR to neutral.
 */
void FNRNeutral(){
	clearABit(0);
	clearABit(1);
	while((PORTA & 0x3) != 0){
		clearABit(0);
		clearABit(1);
		vTaskDelay(1);
	}
}

/*
 * Sets the state of the FNR controller.
 *
 * char FNR: The value to set the FNR.
 *             -1: Reverse
 *              0: Neutral
 *              1: Forward
 */
char setFNR(char FNR) {
	if(FNR == 0){
		FNRNeutral();
	} else if(FNR == 1){
		FNRForward();
	} else if(FNR == -1){
		FNRReverse();
	}
   return 1;
}

/*
 * Gets the current FNR state.
 *
 * char* sensorResponse: A pointer to return the FNR state.
 *                         -1: Reverse
 *                          0: Neutral
 *                          1: Forward
 */
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
   return 1;
}
