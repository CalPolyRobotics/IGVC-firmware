
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "SerialComms.hpp"
#include "CaddyBoardControl.h"

#define COMM_PORT_NUMBER	1        /* /dev/ttyS0 (COM1 on windows) */
#define BAUD_RATE			115200

using namespace std;

int main(int argc, char** argv){

	int successCount = 0,count = 0;
	char input;
	char FNRState;
   int steerState;
	unsigned char cartSpeed;
   ReturnPayload retPayload;
   bool runForever = argv[2][0] == '1';
	
	CaddyBoardControl controller;

	if(controller.initializeComms("/dev/ttyACM1",BAUD_RATE) != COMM_SUCCESS){
		cout << "Unable to initialize Serial Connection\n";
		return 1;
	}	

	cout << "Connection Initialized" << endl;

   controller.setFNRForward();

   //while(1);

   while(1) {
	controller.setFNRReverse();
	usleep(3000000);
	controller.setFNRNeutral();
	usleep(3000000);
	controller.setFNRForward();
	usleep(3000000);
	controller.setFNRNeutral();
	usleep(3000000);
   }

   if(0) {
   do {
		//controller.getSpeed((char)FNRState);
      int i;
      //controller.getHallEffectTicks();
      controller.getAngle();
      //controller.getSpeed();
      //controller.getSonarAll();
      retPayload = controller.getResults();
      if(retPayload.payload){
         //printf("%f\n", (31250.)/((unsigned char)retPayload.payload[1] * 256 + retPayload.payload[0]));
         printf("%u\n", (unsigned int)retPayload.payload[1] * 256 + retPayload.payload[0]);
         /*for(i=0;i < 4;i++) {
            printf("%u ", (unsigned int)retPayload.payload[i*2 + 1] * 256 + retPayload.payload[i*2]);
         }
         printf("\n");*/
         //printf("%d\n", (char)retPayload.payload[0]);
            
      }
      //FNRState++;
      //if(FNRState == 2) FNRState = -1;
      usleep(atoi(argv[1]));
      //usleep(ato);
   } while(1);
   }

   //return 0;
      
	while(scanf("%c",&input) != EOF){
		count = 0;
		switch(input){
		case 'Y':
         steerState = 170;        
         controller.setAngle(steerState);
		   break;
      case 'U':
         steerState = 225;
         controller.setAngle(steerState);
		   break;
      case 'I':
         steerState = 274; 
         controller.setAngle(steerState);
		   break;
      case 'O':
         steerState = 384;
         controller.setAngle(steerState);
		   break;
      case 'P':
         steerState = 410;
         controller.setAngle(steerState);
		   break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			//cartSpeed = 12 * (input - 0x30);
			//sendPacket = speedPacket;
			continue;
      case 'Q':
         controller.toggleMotorDriver();
		default:
			continue;
		}

      //controller.setAngle(steerState);
		//controller.setFNR((char)FNRState);
		/*while(atmega.sendPacket(&sendPacket) != COMM_SUCCESS){
			cout << "Failure sending packet. Trying again\n";
			usleep(100000);
			count++;
			if(count > 5){	
				break;
			}
		}
		if(count > 5){
			cout << "Command unsuccessful!\n";
		} else {
			cout << "Successfully sent command\n";
		}*/
	}

	//results = atmega.getResults();

	/*for(int i = 0;i < results.size;i++){
		cout << "Byte: " << i << " is " << results.payload[i] << endl;
	}*/

	return 0;
}
