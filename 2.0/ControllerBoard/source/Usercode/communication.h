#ifndef _INCL_COMMUNICATION
#define _INCL_COMMUNICATION
/* USER CODE BEGIN (35) */
/*
    .__              .__  __
  ____  ____   _____   _____  __ __  ____ |__| ____ _____  |__|/  |_  ____   ____
_/ ___\/  _ \ /     \ /     \|  |  \/    \|  |/ ___\\__  \ |  \   __\/  _ \ /    \
\  \__(  <_> )  Y Y  \  Y Y  \  |  /   |  \  \  \___ / __ \|  ||  | (  <_> )   |  \
 \___  >____/|__|_|  /__|_|  /____/|___|  /__|\___  >____  /__||__|  \____/|___|  /
     \/            \/      \/           \/        \/     \/                     \/
 *
 *  Created on: Nov 25, 2014
 *      Author: Robotics,  Louie Thiros , Michael Roberts
 */
#include "FreeRTOS.h"
#include "os_task.h"
#include"os_semphr.h"
typedef unsigned char  uint8_t;
#define MAX_PAYLOAD_SIZE 32
#define NACK_BYTE 0x5A
#define ACK_BYTE	128
#define TIMEOUT 5
#define ULTRASONIC_GROUP 0x01
#define SPEED_GROUP 0x02
#define STEERING_GROUP 0x03
#define FNR_GROUP 0x04
#define BRAKES_GROUP 0x05
#define BATTERY_GROUP 0x06
#define LIGHTS_GROUP 0x07
#define ERROR_GROUP 0x08

//ultrasonic commands
#define GET_ALL_SENSORS 0x01
#define GET_CERTAIN_SENSORS 0x02
#define GET_SENSOR_GROUP 0x03

//speed commands
#define GET_SPEED 0x00
#define SET_SPEED 0x01
#define GET_TICKS 0x02

//steering commands
#define SET_ANGLE 0x01
#define GET_ANGLE 0x02
#define GET_DESIRED_ANGLE 0x03
#define CHANGE_PID 0x04
#define SET_LIMITS 0x05
#define RESET_MOTOR_DRIVER 0x06

//FNR commands
#define SET_FNR 0x00
#define GET_FNR 0x01

//brake commands
#define SET_BRAKE 0x00
#define GET_BRAKE 0x01

//battery commands
#define GET_BATTERY_VOLTAGE 0x00
#define GET_STEERING_VOLTAGE 0x01

//light commands
#define SET_LIGHT 0x00

typedef struct {
   char groupID;
   char cmd;
   char size;
   char crc;
   unsigned char payload[MAX_PAYLOAD_SIZE];
} Command;

typedef struct {
   char commandBack;
   char size;
   unsigned char payload[MAX_PAYLOAD_SIZE];
} Response;


//function to CRC the command structure
char commandIntegCheck(Command *command);

//Function that will take in a command (as char array) and process it into a
//correct response to be stored into response
char processCommand(Command *command, Response *response);



char processUltrasonicCommand(char commandCode, void* commandData, Response* responseData);
char processSpeedCommand(char commandCode, void* commandData, Response* responseData);
char processSteeringCommand(char commandCode, void* commandData, Response* responseData);
char processFNRCommand(char commandCode, void* commandData, Response* responseData);
char processBrakeCommand(char commandCode, void* commandData, Response* responseData);
char processBatteryCommand(char commandCode, void* commandData, Response* responseData);
char processLightCommand(char commandCode, void* commandData, Response* responseData);

void sendHeader(Response* response);
void sendPayload(Response* response);
uint8_t calcChecksum(uint8_t* buffer, uint8_t size);
void sendACK(void);
void sendNACK(void);
typedef enum {RecvHeader, RecvPayload, SendHeaderACK, SendPayloadACK} ReadState;

extern int globalTickCount;


void communicationTxtask(void *pvParameters);
void communicationRxtask(void *pvParameters);
void comsetup();
void VTaskCommuncation(void *pvParameters);
SemaphoreHandle_t xSemaphoreSCIDataRX;
SemaphoreHandle_t xSemaphoreSCIDataTX;
SemaphoreHandle_t xRXQueue;
SemaphoreHandle_t xTXQueue;
uint8_t RXdata;
uint8_t TXdata;




#endif




/* USER CODE END */
