/**
 * usart.c
 * Written by Gerik Kubiak.
 *
 * Contains function to use the various USARTs
 * available on the ATmega.
**/

#include "FreeRTOS.h"
#include "semphr.h" 
#include "queue.h"
#include "protocol.h"
#include "task.h"

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "serial.h"

#define WRITE_BUF_SIZE 32

static unsigned char writeBuffer[WRITE_BUF_SIZE];
static int bufSize = 0;

extern unsigned int globalTickCount;

//TODO: Implement a debug USART for debugging information.

/*
 * Initializes the USART used for the serial protocol.
 */
void initializeUSART() {

    UBRRNH = 0; //115200
    UBRRNL = 8;

    UCSRNB = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
    UCSRNC = (1<<UCSZ01)|(1<<UCSZ00);

    bufSize = 0;
}

/*
 * Add one byte the the USART queue.
 */
void USARTQueueVar(char data) {

    if(bufSize < WRITE_BUF_SIZE) {
        writeBuffer[bufSize] = data;
        if(bufSize == 0) {
            if(UCSRNA & (1<<UDRE0)) {
                UDRN = data;
            } else {
                bufSize++;
            }
        } else {
            bufSize++;
        }
    } else {
    }

}

/*
 * Add one or more bytes from a buffer to the queue.
 *
 * char* buf: The buffer which contains the bytes to send.
 * int size: The number of bytes to send.
 */
void USARTQueueBuf(char *buf, int size) {
    int i;
    for(i = 0; i < size; i++) {
        USARTQueueVar(buf[i]);
    }
}

/*
 * The interrupt handler is called after a character has been sent
 * from the USART. Sends the next character in the queue.
 */
ISR(USARTN_TX_vect){
    int i;

    if(bufSize == 0) {
    } else {
        UDRN = writeBuffer[0];
        for(i = 0;i < bufSize; i++) {
            writeBuffer[i] = writeBuffer[i+1];
        }
        bufSize--;
    }

}

/*
 * The interrupt handler is called when a character is received.
 * The character is relayed to the serial protocol state machine.
 */
ISR(USARTN_RX_vect){
    runSerialFSM(UDRN);
}

/*
 * Sends a number across the serial connection with a hexadecimal format.
 */
void printHex(int i){
	char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	USARTQueueVar(hex[(i&0xF000) >> 12]);
	USARTQueueVar(hex[(i&0xF00) >> 8]);
	USARTQueueVar(hex[(i&0xF0) >> 4]);
	USARTQueueVar(hex[i&0xF]);
}

/*
 * Sends a number across the serial connection in a decimal format.
 */
void printNum(unsigned int i){
    
	USARTQueueVar(i / 10000 + '0');
	USARTQueueVar((i % 10000) / 1000 + '0');
	USARTQueueVar((i % 1000) / 100 + '0');
	USARTQueueVar((i % 100) / 10 + '0');
   USARTQueueVar((i % 10) + '0');
}
