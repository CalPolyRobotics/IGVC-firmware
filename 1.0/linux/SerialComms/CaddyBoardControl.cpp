#include "SerialComms.hpp"
#include "CaddyBoardControl.h"

#include <iostream>
#include "unistd.h"

#define RETRY_TIME 100

int CaddyBoardControl::sendCommand(Packet *packet) {

   int count = 0;

   while(atmega.sendPacket(packet) != COMM_SUCCESS){
		std::cerr << "Failure sending packet. Trying again\n";
		usleep(RETRY_TIME);
		count++;
		if(count > 5){
			break;
		}
	}
	if(count > 5){
		std::cerr << "Command unsuccessful!\n";
		return -1;
	} else {
		std::cerr << "Successfully sent command\n";
		return 0;
	}
}

COMM_STATUS CaddyBoardControl::initializeComms(char* portStr, int baud){
	atmega.initializeComms(portStr,baud);
}

int CaddyBoardControl::setFNR(char direction){

	int count = 0;
	Packet FNRPacket = {4,0,1,0};
	FNRPacket.payload = (unsigned char*)&direction;
		
	while(atmega.sendPacket(&FNRPacket) != COMM_SUCCESS){
		std::cerr << "Failure sending packet. Trying again\n";
		usleep(RETRY_TIME);
		count++;
		if(count > 5){
			break;
		}
	}
	if(count > 5){
		std::cerr << "Command unsuccessful!\n";
		return -1;
	} else {
		std::cerr << "Successfully sent command\n";
		return 0;
	}
}

int CaddyBoardControl::setAngle(int ang){

  int count = 0;
	Packet FNRPacket = {3,1,4,0};
	FNRPacket.payload = (unsigned char*)&ang;
		
	while(atmega.sendPacket(&FNRPacket) != COMM_SUCCESS){
		std::cerr << "Failure sending packet. Trying again\n";
		usleep(RETRY_TIME);
		count++;
		if(count > 5){
			break;
		}
	}
	if(count > 5){
		std::cerr << "Command unsuccessful!\n";
		return -1;
	} else {
		std::cerr << "Successfully sent command\n";
		return 0;
	}
} 

int CaddyBoardControl::getFNR(){
   
   Packet FNRPacket = {4, 1, 0, 0,};

   return sendCommand(&FNRPacket);
}

int CaddyBoardControl::getAngle(){

   int count = 0;
	Packet FNRPacket = {3,2,0,0};
		
	while(atmega.sendPacket(&FNRPacket) != COMM_SUCCESS){
		std::cerr << "Failure sending packet. Trying again\n";
		usleep(RETRY_TIME);
		count++;
		if(count > 5){
			break;
		}
	}
	if(count > 5){
		std::cerr << "Command unsuccessful!\n";
		return -1;
	} else {
		std::cerr << "Successfully sent command\n";
		return 0;
	}
} 

int CaddyBoardControl::getSpeed(){

   Packet speedPacket = {2, 0, 0, 0};

   return sendCommand(&speedPacket);
}

int CaddyBoardControl::getSonar(int sonar){
   
   Packet sonarPacket = {1, 2, 1, 0};
   sonarPacket.payload = (unsigned char*)&sonar;

   return sendCommand(&sonarPacket);
}

int CaddyBoardControl::getSonarGroup(int group){
   
   Packet sonarPacket = {1, 3, 1, 0};
   sonarPacket.payload = (unsigned char*)&group;

   return sendCommand(&sonarPacket);
}

int CaddyBoardControl::getSonarAll(){
   
   Packet sonarPacket = {1, 1, 0, 0};

   return sendCommand(&sonarPacket);
}

int CaddyBoardControl::getHallEffectTicks(){

   Packet hallPacket = {2, 2, 0, 0};

   return sendCommand(&hallPacket);
}

int CaddyBoardControl::toggleMotorDriver(){
   
   int count = 0;
   Packet motorPacket = {3,6,0,0};

   while(atmega.sendPacket(&motorPacket) != COMM_SUCCESS){
   	std::cerr << "Failure sending packet. Trying again\n";
		usleep(RETRY_TIME);
		count++;
		if(count > 5){
			break;
		}
	}
	if(count > 5){
		std::cerr << "Command unsuccessful!\n";
		return -1;
	} else {
		std::cerr << "Successfully sent command\n";
		return 0;
	}
}
