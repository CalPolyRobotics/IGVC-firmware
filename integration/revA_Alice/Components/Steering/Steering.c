/*
 * Steering.c
 * Written by Gerik Kubiak.
 *
 * Contains code to steer the golf cart to a specific
 * angle represented by an linear encoder value.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "task.h"
#include "../../ADC.h"
#include "../../usart.h"
#include "Steering.h"

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

#define MAX_STEERING_CURRENT (.0659*4 + 2.53)
#define MIN_STEERING_CURRENT (-.0659*4 + 2.53)

static int steeringTarget;
static int steeringValue;
static int motorCurrent;

static int steeringDir;

static int zeroCurrentDelay;

void printWheelAngle(void);
void getLinearPotCallback(int data, void *parameters);
void getMotorCurrentCallback(int data, void *parameters);

/*
 * The ADC callback for the linear encoder.
 *
 * int data: The data from the ADC.
 */
void getLinearPotCallback(int data,void *parameters){
   steeringValue = data;
}

void getMotorCurrentCallback(int data, void *parameters){
   motorCurrent = data;
   printNum(data);
   USARTQueueBuf("\r\n", 2);
}

/*
 * Initialize the timing registers used to pwm the motor controllers.
 */
void initializeSteeringTimer(){
	
   TCCR1A = (1 << WGM11)|(1 << COM1A1);
   TCCR1B = (1 << WGM12)|(1 << CS10)|(1 << CS11);
   TCCR1C = 0;
}

/*
 * Sets the appropriate PWM duty cycle and direction
 * based on the steering Direction and speed.
 *
 * int spd: A value representing how fast to move the motor.
 */
void setSteeringPWMSpeed(int spd){
   if(spd > 0x3FF) spd = 0x3FF;

   /*if(motorCurrent > MAX_STEERING_CURRENT
      || motorCurrent < MIN_STEERING_CURRENT) {
      spd = (spd*3) / 4;
   }*/

   //OCR1AH = spd >> 8;
   //OCR1AL = spd & 0xFF;
   OCR1AH = 1;
   OCR1AL = 0x40;

   if(steeringDir == -1) {
      PORTB |= (1 << PB4);
   } else if(steeringDir == 1) {
      PORTB &= ~(1 << PB4);
   } else {
      OCR1AH = 0;
      OCR1AL = 0;
   }
}

/*
 * Sets the direction to steer the motor.
 * 
 * int dir: Either 1 or -1. Which direction this results in 
 * depends on how the motor is connected.
 */
void setSteeringDirection(int dir){
   steeringDir = dir;
}

/*
 * Sets the target angle as a target linear encoder value.
 *
 * unsigned char* angleTarget: The target linear encoder value.
 */
char setAngle(unsigned char* angleTarget) {
	steeringTarget = angleTarget[0];
   steeringTarget |= (angleTarget[1] << 8);
   zeroCurrentDelay = STEERING_DELAY;
   return 1;
}

/*
 * Gets the current linear encoder value.
 *
 * unsigned char* sensorResponse: A pointer where to put the current
 *                                linear encoder value.
 */
char getAngle(unsigned char* sensorResponse) {
   sensorResponse[0] = (unsigned char)(steeringValue & 0xFF);
   sensorResponse[1] = (unsigned char)(steeringValue >> 8);
   return 1;
}

/*
 * Get the current target linear encoder angle.
 *
 * unsigned char* sensorResponse: A pointer where to put the current
 *                                target linear encoder value.
 */
char getDesiredAngle(unsigned char* sensorResponse) {
   sensorResponse[0] = (unsigned char)(steeringTarget & 0xFF);
   sensorResponse[1] = (unsigned char)(steeringTarget >> 8);
   return 1;
}

/*
 * Change PID sensitivity. Not currently implemented. May never be.
 */
char changePID(char P, char I, char D) {
   return 1;
}

/*
 * Sets the upper and lower bounds to steer the golf cart. Not currently implemented.
 */
char setLimits(char upper, char lower) {
   return 1;
}

/*
 * Prints the current wheel angle over serial. Disrupts the serial communication protocol.
 */
void printWheelAngle() {
   if(steeringValue & 0x1000) {
      USARTQueueVar('-');
      steeringValue *= -1;
   }      
   printNum(steeringValue);
   USARTQueueVar('\r');
   USARTQueueVar('\n');
}

/*
 * Task used to steer the golf cart. Implements a basic P controller.
 */
void vTaskSteer(void* parameters){

	addADCDevice(0,ADC_OPT_PRECISION_HIGH,getLinearPotCallback,NULL);
   addADCDevice(2,ADC_OPT_PRECISION_HIGH,getMotorCurrentCallback,NULL);

   PORTB |= (1 << PB4);

   initializeSteeringTimer();

   OCR1AH = 0;
   OCR1AL = 0;

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
	   }
   
      if(zeroCurrentDelay > 0){
         zeroCurrentDelay--;
         setSteeringPWMSpeed(((adjust + 140) / STEERING_DELAY) * (STEERING_DELAY - zeroCurrentDelay));
      } else {

         setSteeringPWMSpeed(adjust + 140);
      }
 
	   vTaskDelay(10);
	}

}

