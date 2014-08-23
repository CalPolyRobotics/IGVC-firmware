// Code to controller the Sonar sensors
#include "FreeRTOS.h"
#include "semphr.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#include "../../protocol.h"
#include "../../ADC.h"
#include "Sonar.h"

void sonarADCHandler(int result, void *sonarNum);

static int sonarData[6];
static int sonarNum0 = 0;
static int sonarNum1 = 1;
static int sonarNum2 = 2;
static int sonarNum3 = 3;

void setSonarData(int i,int data){
   sonarData[i] = data;
}

int getSonarData(int i){
   return sonarData[i];
   //return i + 10;
}

void sonarADCHandler(int result,void *sonarNum){

	setSonarData(*((int *)sonarNum),result);

}

void initializeSonarSensors(){

	addADCDevice(1,ADC_OPT_PRECISION_HIGH,sonarADCHandler,&sonarNum0);			
   addADCDevice(2,ADC_OPT_PRECISION_HIGH,sonarADCHandler,&sonarNum1);
	addADCDevice(3,ADC_OPT_PRECISION_HIGH,sonarADCHandler,&sonarNum2);			
	addADCDevice(4,ADC_OPT_PRECISION_HIGH,sonarADCHandler,&sonarNum3);			

}

char getAllSensors(unsigned char* responseData){
   unsigned short i;
   for(i=0;i<6;i++){
      responseData[i*2] = (unsigned char)(getSonarData(i) & 0xFF);
      responseData[i*2 + 1] = (unsigned char)(getSonarData(i) >> 8);
      //responseData[i] = i+1;
   }
   return 1;
}

char getCertainSensor(unsigned char commandData,unsigned char* responseData){

   if(commandData < 6){
      responseData[0] = (unsigned char)(getSonarData(commandData) & 0xFF);
      responseData[1] = (unsigned char)(getSonarData(commandData) >> 8);
   }
   return 1;
}

char getSensorGroup(unsigned char commandData,unsigned char* responseData){

   switch(commandData){
      case SONAR_GROUP_LEFT:
         responseData[0] = (unsigned char)(getSonarData(0) & 0xFF);
         responseData[1] = (unsigned char)(getSonarData(0) >> 8);
         responseData[2] = (unsigned char)(getSonarData(1) & 0xFF);
         responseData[3] = (unsigned char)(getSonarData(1) >> 8);
         break;

      case SONAR_GROUP_FRONT:
         responseData[0] = (unsigned char)(getSonarData(4) & 0xFF);
         responseData[1] = (unsigned char)(getSonarData(4) >> 8);
         responseData[2] = (unsigned char)(getSonarData(5) & 0xFF);
         responseData[3] = (unsigned char)(getSonarData(5) >> 8);
         break;

      case SONAR_GROUP_RIGHT:
         responseData[0] = (unsigned char)(getSonarData(2) & 0xFF);
         responseData[1] = (unsigned char)(getSonarData(2) >> 8);
         responseData[2] = (unsigned char)(getSonarData(3) & 0xFF);
         responseData[3] = (unsigned char)(getSonarData(3) >> 8);
         break;

   }
   return 1;

}
