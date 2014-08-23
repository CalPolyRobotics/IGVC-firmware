
#include <avr/io.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "usart.h"
#include "protocol.h"

#define NACK_BYTE 0x5A
#define ACK_BYTE	128

#define TIMEOUT 5

void sendHeader(Response* response);
void sendPayload(Response* response);
uint8_t calcChecksum(uint8_t* buffer, uint8_t size);
void sendACK(void);
void sendNACK(void);
 

typedef enum {RecvHeader, RecvPayload, SendHeaderACK, SendPayloadACK} ReadState;

extern int globalTickCount;

//Run one instance of the serial Communication FSM. This is called
//from the USART RX interrupt. Therefore there should be minimal code here
void runSerialFSM(unsigned char data) {

    static ReadState FSMState = RecvHeader;
    static int oldCount = 0;
    static int bytesRecieved = 0;
    static unsigned char buffer[4];
    static Command command;
    static Response response;

    if(globalTickCount - oldCount >= TIMEOUT) { 
        bytesRecieved = 0;
        FSMState = RecvHeader;
    }

    oldCount = globalTickCount;

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

void sendHeader(Response* response){
    uint8_t checksumBuffer[2];

    USARTQueueVar(response->commandBack);
    USARTQueueVar(response->size);
    checksumBuffer[0] = response->commandBack;
    checksumBuffer[1] = response->size;
    USARTQueueVar((uint8_t)calcChecksum(checksumBuffer,2));
}

void sendPayload(Response* response){
    USARTQueueBuf((char*)response->payload, response->size);
    USARTQueueVar(calcChecksum((uint8_t*)response->payload,response->size));
}

uint8_t calcChecksum(uint8_t* buffer, uint8_t size){
   uint8_t checksum = 0;
   int i;   
   for(i = 0; i < size; i++) {
       checksum += *(buffer++);
   }
   return checksum;
}

void sendACK() {
   USARTQueueVar(ACK_BYTE);
}

void sendNACK() {
   USARTQueueVar(NACK_BYTE);
}
