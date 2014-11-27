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
 *      Author: Robotics
 */

#include "communication.h"
#include "ssi.h"

char  data[100];
// addtx queue

void sciNotification(sciBASE_t *sci, uint32 flags)
{

if(// if data is redy to be tranmitted )
		{

	// unlock mutex
		}
if(/// if data is ready read)
		{
	   // incremented counting semiphor

		}


}


void USARTQueueBuf(char *buf, int size) {
// add to queue;

}

/*
 * Add one byte the the USART queue.
 */
void USARTQueueVar(char data) {
	USARTQueueBuf(&data, 1);

}

void communicationtxtask()
{
	while(1)
	{
		if(//data data on queue )
				{
			if(/ and mutex not set)
			{
				for(int i = 0 ; i < 100; i++)
			 {
				 if( queue is empty )
					 break;
				 data[i] = // deque data from queue


			 }
				// set mutex
				sciSendByte(,buf,size)

			}
				}


	}


}

// rx queue
void communicationRxtask(void *pvParameters)
{

for(;; )
{
// block if the counting semiphore does not have data
if()
{
	// copy over 100 bytes or the  counting semiphore size
	 // decremented counting semiphore
	// lock rx mutex trsnation
     // perform  rx mutex tranation

	if(/// is transation mutex unlocked  block )
			{

		for(int i = 0; i < amount of data ;  i++)
		{
	         /// enqueue data;
		}

	// unlock transation
			}
}


}

}


/*
 * Gets data from the Ultrasonic sensors.
 *
 * char commandCode: The specific command to call.
 * void* commandData: Data from the master to pass to the device.
 * Response* responseData: The response from the device.
 */
char processUltrasonicCommand(char commandCode, void* commandData, Response* responseData) {
   switch(commandCode) {
      case GET_ALL_SENSORS:
         //responseData->size = 12;
         //getAllSensors((unsigned char*) responseData->payload);
         break;
      case GET_CERTAIN_SENSORS:
         //responseData->size = 2;
        // getCertainSensor(((unsigned char*)commandData)[0], (unsigned char*) responseData->payload);
         break;
      case GET_SENSOR_GROUP:
         //responseData->size = 4;
         //getSensorGroup(((unsigned char*)commandData)[0], (unsigned char*) responseData->payload);
         break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processSpeedCommand(char commandCode, void* commandData, Response* responseData) {
   switch(commandCode) {
      case GET_SPEED:
         //responseData->size = 2;
        // getSpeed((unsigned char*) responseData->payload);
         break;
      case SET_SPEED:
			//responseData->size = 0;
         setSpeed(((char*)commandData)[0]);
         break;
      case GET_TICKS:
         //responseData->size = 2;
         //getTicks((unsigned char*) responseData->payload);
         break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processSteeringCommand(char commandCode, void* commandData, Response* responseData) {

   switch(commandCode) {
      case SET_ANGLE:
         setAngle(((unsigned char*)commandData));
	      //responseData->size = 0;
         break;
      case GET_ANGLE:
        // responseData->size = 2;
        // getAngle((unsigned char*) responseData->payload);
         break;
      case GET_DESIRED_ANGLE:
         //responseData->size = 2;
        // getDesiredAngle((unsigned char*) responseData);
         break;
      case CHANGE_PID:
        // changePID(((char*)commandData)[0], ((char*)commandData)[1], ((char*)commandData)[2]);
         break;
      case SET_LIMITS:
         //setLimits(((char*)commandData)[0], ((char*)commandData)[1]);
         break;
      case RESET_MOTOR_DRIVER:
        // PORTJ ^= (1 << PJ4);
         break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processFNRCommand(char commandCode, void* commandData, Response* responseData) {
   switch(commandCode) {
      case SET_FNR:
	      responseData->size = 0;
         //setFNR(*((char*)commandData));
         break;
      case GET_FNR:
         responseData->size = 1;
       //  getFNR((char*) responseData->payload);
         break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processBrakeCommand(char commandCode, void* commandData, Response* responseData) {
   switch(commandCode) {
      case SET_BRAKE:
	 //setBrake(*((char*)commandData));
	 break;
      case GET_BRAKE:
	 //getBrake((char*) responseData);
	 break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processBatteryCommand(char commandCode, void* commandData, Response* responseData) {
   switch(commandCode) {
      case GET_BATTERY_VOLTAGE:
         //getBatteryVoltage((char*) responseData);
         break;
      case GET_STEERING_VOLTAGE:
        // getSteeringVoltage((char*) responseData);
         break;
   }
   return 1;
}

/*
 * Similar to the Ultrasonic.
 */
char processLightCommand(char commandCode, void* commandData, Response* responseData) {
	responseData->size = 0;
   switch(commandCode) {
   case SET_LIGHT:
	 	//setLight(*((char*)commandData));
      break;
   }
   return 1;
}

/*
 * Takes in a command, calls the appropriate function, and returns the result.
 *
 * Command* command: The incoming command.
 * Response* response: The response to send back.
 */
char processCommand(Command* command, Response* response) {
	response->commandBack = command->cmd;

   switch(command->groupID) {
      case ULTRASONIC_GROUP:
         //processUltrasonicCommand(command->cmd, command->payload, response);
         break;
      case SPEED_GROUP:
			//processSpeedCommand(command->cmd,command->payload,response);
         break;
      case STEERING_GROUP:
         //PORTC = response->commandBack;
         //processSteeringCommand(command->cmd,command->payload,response);
         break;
      case FNR_GROUP:
			//processFNRCommand(command->cmd,command->payload,response);
         break;
      case BRAKES_GROUP:
         /*do brakes things*/
         break;
      case BATTERY_GROUP:
        // processBatteryCommand(command->cmd,command->payload,response);
         break;
      case LIGHTS_GROUP:
	      //processLightCommand(command->cmd,command->payload,response);
         break;
      case ERROR_GROUP:
         /*do error things*/
         break;
   }
   return 1;
}


void runSerialFSM(unsigned char data) {

    static ReadState FSMState = RecvHeader;
    static int oldCount = 0;
    static int bytesRecieved = 0;
    static unsigned char buffer[4];
    static Command command;
    static Response response;

    if(xTaskGetTickCount() - oldCount >= TIMEOUT) {
        bytesRecieved = 0;
        FSMState = RecvHeader;
    }

    oldCount = xTaskGetTickCount();

    switch(FSMState) {
    case RecvHeader:
        buffer[bytesRecieved] = data;
        bytesRecieved++;

        if(bytesRecieved == 4) {
            command.groupID = buffer[0];
            command.cmd = buffer[1];
            command.size = buffer[2];
            command.crc = buffer[3];

            if(calcChecksum(buffer,3) == command.crc) {
                bytesRecieved = 0;

                if(command.size > 0) {
                    sendACK();
                    FSMState = RecvPayload;
                } else {
                    sendACK();
                    processCommand(&command, &response);
                    sendHeader(&response);
                    FSMState = SendHeaderACK;
                }

            } else {
                sendNACK();
                bytesRecieved = 0;
            }
        }
        break;

    case RecvPayload:
        if(bytesRecieved != command.size) {
            command.payload[bytesRecieved] = data;
            bytesRecieved++;
        } else {
            bytesRecieved = 0;
            if(calcChecksum(command.payload, command.size) == data) {
                sendACK();
                processCommand(&command, &response);
                sendHeader(&response);
                FSMState = SendHeaderACK;
            } else {
                sendNACK();
                bytesRecieved = 0;
                FSMState = RecvHeader;
            }
        }
        break;

    case SendHeaderACK:
        if(data == ACK_BYTE) {
            if(response.size == 0) {
                bytesRecieved = 0;
                FSMState = RecvHeader;
            } else {
                sendPayload(&response);
                FSMState = SendPayloadACK;
            }
        } else {
            bytesRecieved = 0;
            FSMState = RecvHeader;
        }
        break;

    case SendPayloadACK:
        bytesRecieved = 0;
        FSMState = RecvHeader;
        break;

    }

}

/*
 * Send the header packet to start the response.
 *
 * Response* response: The response struct to base the header off of.
 */
void sendHeader(Response* response){
    uint8_t checksumBuffer[2];

    USARTQueueVar(response->commandBack);
    USARTQueueVar(response->size);
    checksumBuffer[0] = response->commandBack;
    checksumBuffer[1] = response->size;
    USARTQueueVar((uint8_t)calcChecksum(checksumBuffer,2));
}

/*
 * Send the payload response.
 *
 * Response* response: The response containing the payload and size.
 */
void sendPayload(Response* response){
    USARTQueueBuf((char*)response->payload, response->size);
    USARTQueueVar(calcChecksum((uint8_t*)response->payload,response->size));
}

/*
 * Calculates the approprite checksum for a buffer. The checksum
 * is calculated by adding all the bytes and tossing the overflow.
 *
 * uint8_t* buffer: The buffer to calculate the checksum for.
 * uint8_t size: The size of the buffer in bytes.
 *
 * return: The correct checksum.
 */
uint8_t calcChecksum(uint8_t* buffer, uint8_t size){
   uint8_t checksum = 0;
   int i;
   for(i = 0; i < size; i++) {
       checksum += *(buffer++);
   }
   return checksum;
}

/*
 * Helper function to send an Acknowledgement byte.
 */
void sendACK() {
   USARTQueueVar(ACK_BYTE);
}

/*
 * Helper function to send a non-Acknowledgement byte.
 */
void sendNACK() {
   USARTQueueVar(NACK_BYTE);
}



void VTaskCommuncation(void *pvParameters)
{
    xSemaphore = xSemaphoreCreateBinary();

    for(;;)
    {
      /// check if there is data on the queue
      if()
      {
    	  // data left on the queue
    	while()
    	runSerialFSM(unsigned char data)
      }
    }   
}



/* USER CODE END */
