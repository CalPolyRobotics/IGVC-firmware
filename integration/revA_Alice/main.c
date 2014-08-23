#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void vTaskFunction_1(void);
void vTaskFunction_2(void);
void vTaskFunction_3(void);
void vTaskPot(void);
int potValue(int sonarMax,int sonarMin,int potMax,int potMin,int x);
void vApplicationTickHook(void);
void vApplicationStackOverflowHook(void);
void printNum(unsigned int i);
void printHex(int i);
void testHandle(int data, void* param);
void testHandle2(int data, void* param);
void delay(int);

int globalTickCount = 0;

int sonarTime;

void vApplicationTickHook()
{
    globalTickCount++;
}

void vApplicationStackOverflowHook(){
	return;
}
/*-----------------------------------------------------------*/

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
	DDRJ = 0x02 | (1 << PJ5);
   DDRK = 0;
   DDRL = 0xF0;

   PORTB = 0;
	PORTD = 0;
	PORTE = 0;
   PORTJ = 0;

	//- Create a 
	xTaskCreate( (pdTASK_CODE) vTaskFunction_1, (signed char *) "T0", configMINIMAL_STACK_SIZE+1000,
                NULL, 2, NULL );

	//xTaskCreate( (pdTASK_CODE) vTaskPot, (signed char *) "T0", configMINIMAL_STACK_SIZE+1000,
                //NULL, 1, NULL );

  	xTaskCreate( (pdTASK_CODE) vTaskSteer, (signed char *) "T4", configMINIMAL_STACK_SIZE+1000,
                NULL, 2, NULL );
 
   xTaskCreate( (pdTASK_CODE) vTaskADC, (signed char *) "T5", configMINIMAL_STACK_SIZE+1000,
   				NULL, 2, NULL);
    
    //- kick off the scheduler
	vTaskStartScheduler();
    
	return 0;
}
/*-----------------------------------------------------------*/



int potValue(int sonarMax,int sonarMin,int potMax,int potMin,int x){
	int value;	
	if(x < sonarMin){
		return potMin;
	} else if (x > sonarMax){
		return potMax;
	} else {
		value = x / 4 - 140;
		return value > potMax?potMax:value < potMin?potMin:value;
	}
} 

void testHandle(int data, void* param) {
   printHex(data);
   USARTQueueBuf("\r\n", 2);
}

void vTaskFunction_1()
{	
	int sonarResult;
	int movingForward = 1;

	int sonarMax = 0x31C;
	int sonarMin = 0xE0;
	int potMin = 0x18;
	int potMax = 0x40;;
	int backwardSwitch = 0x100;
	int neutralSwitch = 0x140;
	int forwardSwitch = 0x160;
	int minTicks = 450;

	int tickCount;

	/*initializeSteeringTimer();

	initializeSPI();
	initSpeedController();
   initializeBattery();*/
   initializeSonarSensors();
   initializeUSART();
   initializeSPI();
   //initializeHallEffect();

   //addADCDevice(0, 0, testHandle, NULL);

   for(;;) {
      /*if(PINF & 1) {
         USARTQueueBuf("High\r\n", 6);
      } else {
         USARTQueueBuf("Low\r\n", 5);
      }*/
      vTaskDelay(500);
   }
   
   unsigned int hallEffect;
   printHex(0xAA);
   USARTQueueBuf("\r\n", 2);

   for(;;) {
      getSpeed((unsigned char*)&hallEffect);
      printNum(hallEffect);
      USARTQueueBuf("\r\n", 2);
      vTaskDelay(500);
   }

	for(;;){
		int sonarData = getSonarData(0);
		if(sonarData > 0x300){
			setSteeringDirection(1);
			USARTQueueVar('F');
		} else if(sonarData < 0x50){
			setSteeringDirection(-1);
			USARTQueueVar('R');
		} else {
			setSteeringDirection(0);
			USARTQueueVar('N');
		}
		vTaskDelay(10);	
	}
	
	//PORTC = 0x2;
	setFNR(1);
	
	for(;;){

		//sonarResult = getSonarResult();
		if(movingForward == 1){
			if(sonarResult < backwardSwitch) {
				movingForward = -1;
				setFNR(-1);
				tickCount = 0;
			} else if(sonarResult < neutralSwitch){
				setFNR(0);
				movingForward = 0;
				tickCount = 0;
			}
			setPot(potValue(sonarMax,sonarMin,potMax,potMin,sonarResult));
		} else if(movingForward == 0){
			if(sonarResult < backwardSwitch){
				movingForward = -1;
				setFNR(-1);
				tickCount = 0;
			} if(tickCount > minTicks){
				movingForward = 1;
				setFNR(1);
			}	
		} else {
			if(sonarResult > forwardSwitch && tickCount > minTicks){
				movingForward = 1;
				setFNR(0);
				vTaskDelay(100);
				setFNR(1);
			}
			setPot(potValue(sonarMax,sonarMin,potMax,potMin,sonarResult));
		}
		/*printHex(potValue(sonarMax,sonarMin,potMax,potMin,sonarResult));
		USARTQueueVar('\n');
		USARTQueueVar('\r');*/
		vTaskDelay(1);
		tickCount++;
	}

	for(;;){
		PORTL = 0x10;
		vTaskDelay(200);
		PORTL = 0x20;
		vTaskDelay(200);
		PORTL = 0x40;
		vTaskDelay(200);
		PORTL = 0x80;
		vTaskDelay(200);
	}
}

void vTaskFunction_2(){
	DDRL = 0xF0;
	PORTL = 0xC0;
	for(;;){
		vTaskDelay(300);
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
