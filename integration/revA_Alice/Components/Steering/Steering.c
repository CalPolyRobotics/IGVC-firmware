#include <avr/io.h>
#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "task.h"
#include "../../ADC.h"
#include "Steering.h"
//Steering group

#define STEERING_PORT	PORTB
#define STEERING_LEFT	(1 << 5)
#define STEERING_RIGHT	(1 << 4)

#define STEERING_LEFT_COM0 COM1A0
#define STEERING_LEFT_COM1 COM1A1

#define STEERING_RIGHT_COM0 COM1B0
#define STEERING_RIGHT_COM1 COM1B1

#define STEERING_LEFT_CMPH OCR1AH
#define STEERING_LEFT_CMPL OCR1AL
#define STEERING_RIGHT_CMPH OCR1BH
#define STEERING_RIGHT_CMPL OCR1BL

#define STEERING_DELAY 270

static int steeringTarget;
static int steeringValue;

static int steeringDir;
static int steeringSpd;

static int zeroCurrentDelay;

void printHex(int a);
void printNum(int a);
void USARTQueueVar(char a);
void printWheelAngle(void);
void getLinearPotCallback(int data, void *parameters);


void getLinearPotCallback(int data,void *parameters){
	//wheelAngle = data / -4 + 72;
   steeringValue = data;
}

void initializeSteeringTimer(){
	
	//TCCR1A = (1 << COM1A1)|(1 << WGM11);
   TCCR1A = (1 << WGM11)|(1 << WGM10)|(1 << COM1B1)|(1 << COM1B0)|
      (1 << COM1C1)|(1 << COM1C0);
	TCCR1B = (1 << WGM12)|(1 << CS10);
	TCCR1C = 0;

   OCR1BH = 0;
   OCR1BL = 0;

   OCR1CH = 0;
   OCR1CL = 0;
}

void setSteeringPWMSpeed(int spd){
   steeringSpd = spd * steeringDir;

   if(spd > 0x3FF) spd = 0x3FF;

   if(steeringDir == -1) {
      OCR1BH = 0;
      OCR1BL = 0;
      OCR1CH = spd >> 8;
      OCR1CL = spd & 0xFF;
   } else if(steeringDir == 1) {
      OCR1BH = spd >> 8;
      OCR1BL = spd & 0xFF;
      OCR1CH = 0;
      OCR1CL = 0;
   } else {
      OCR1BH = 0;
      OCR1BL = 0;
      OCR1CH = 0;
      OCR1CL = 0;
   }
}



void setSteeringDirection(int dir){
   steeringDir = dir;
}

//JUST SETS ANGLE TARGET. Actual angle changing is lower level
char setAngle(unsigned char* angleTarget) {
	steeringTarget = angleTarget[0];
   steeringTarget |= (angleTarget[1] << 8);
   zeroCurrentDelay = STEERING_DELAY;
   return 1;
}

//get the current angle of the steering system
char getAngle(unsigned char* sensorResponse) {
   sensorResponse[0] = (unsigned char)(steeringValue & 0xFF);
   sensorResponse[1] = (unsigned char)(steeringValue >> 8);
   //return success
   return 1;
}

//get the angle target. argument name is sensorResponse for the sake of consistancy
char getDesiredAngle(unsigned char* sensorResponse) {
   sensorResponse[0] = (unsigned char)(steeringTarget & 0xFF);
   sensorResponse[1] = (unsigned char)(steeringTarget >> 8);
   //return success
   return 1;
}

//change the PID controller
char changePID(char P, char I, char D) {
   //dummy function, nothing happens
   //return success
   return 1;
}

//not sure what this does. Also not sure why upper and lower are separated
//but its in the specs so...
char setLimits(char upper, char lower) {
   //dummy function, nothing happens
   //return success
   return 1;
}

void printWheelAngle() {
   if(steeringValue & 0x1000) {
      USARTQueueVar('-');
      steeringValue *= -1;
   }      
   printNum(steeringValue);
   USARTQueueVar('\r');
   USARTQueueVar('\n');
}

void vTaskSteer(void* parameters){


	addADCDevice(0,ADC_OPT_PRECISION_HIGH,getLinearPotCallback,NULL);

	int pConst = 80; 
	int adjust;
   
   zeroCurrentDelay = 5;

	steeringTarget = 277;
	while(1){
      
	   adjust = pConst * (steeringTarget - steeringValue);
	   if(adjust < steeringTarget - pConst){
	      setSteeringDirection(-1);
         adjust *= -1;
	   } else if (adjust > steeringTarget + pConst){
	      setSteeringDirection(1);
	   } else {
	      setSteeringDirection(0);
	      //steeringTarget = wheelAngle;
	   }

      if(zeroCurrentDelay > 0){
         zeroCurrentDelay--;
         setSteeringPWMSpeed(((adjust + 140) / STEERING_DELAY) * (STEERING_DELAY - zeroCurrentDelay));
      } else {

         setSteeringPWMSpeed(adjust + 140);
      }
      //printNum(adjust + 50);
      //USARTQueueVar(' ');
      //printWheelAngle();
 
	   vTaskDelay(10);
	}

}

