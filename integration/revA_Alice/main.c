/**
 * main.c
 * Written by Gerik Kubiak.
 * 
 * This file initializes the RTOS environment and 
 * contains one task. This task initializes other
 * devices and then enters an infinite loop.
 *
**/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "task.h"
#include "usart.h"
#include "queue.h"
#include "spi.h"
#include "ADC.h"
#include "Components/FNR/FNR.h"
#include "Components/Speed/Speed.h"
#include "Components/Speed/HallEffect.h"
#include "Components/Sonar/Sonar.h"
#include "Components/Battery/Battery.h"
#include "Components/Steering/Steering.h"

void vApplicationTickHook(void);
void vApplicationStackOverflowHook(void);
void vTaskMain(void);
void vTaskPot(void);

int globalTickCount = 0;

void vApplicationTickHook()
{
    globalTickCount++;
}

void vApplicationStackOverflowHook(){
	return;
}

/*
 * Initializes Ports, creates tasks, and starts the scheduler.
 */
int main( void )
{
    
	DDRA = 0xF7;
	PORTA = 0;
	DDRB = 0xF7; 
   DDRC = 0;
	DDRD = 0xFB;
	DDRE = 0xFE;
   DDRF = 0;
   DDRG = 0;
   DDRH = 0xFE;
   //DDRJ = (1 << 1)|(1 << 4);
   DDRJ = 0xFF;
   DDRK = 0;
   DDRL = 0xF0;

   PORTB = 0;
	PORTD = 0;
	PORTE = 0;
   PORTJ = 0;

	xTaskCreate( (pdTASK_CODE) vTaskMain, (signed char *) "T0", configMINIMAL_STACK_SIZE+1000,
                NULL, 2, NULL );

	//xTaskCreate( (pdTASK_CODE) vTaskPot, (signed char *) "T0", configMINIMAL_STACK_SIZE+1000,
                //NULL, 1, NULL );

  	xTaskCreate( (pdTASK_CODE) vTaskSteer, (signed char *) "T4", configMINIMAL_STACK_SIZE+1000,
                NULL, 2, NULL );
 
   xTaskCreate( (pdTASK_CODE) vTaskADC, (signed char *) "T5", configMINIMAL_STACK_SIZE+1000,
   				NULL, 2, NULL);
    
	vTaskStartScheduler();
    
	return 0;
}

/*
 * Initializes various devices and enters a infinite loop.
 */
void vTaskMain()
{ 
	/*initializeSteeringTimer();

	initializeSPI();
	initSpeedController();
   initializeBattery();*/
   initializeSonarSensors();
   initializeUSART();
   initializeSPI();
   initializeHallEffect();

   for(;;) {
      vTaskDelay(800);
      PORTA ^= 0xE0;
   }
}


void vTaskPot(){
   initSpeedController();

	for(;;){
		setPot(1);
		vTaskDelay(500);
		setPot(0x40);
		vTaskDelay(500);
		setPot(0x7F);
		vTaskDelay(500);
		setPot(0x40);
		vTaskDelay(500);
	}
}
