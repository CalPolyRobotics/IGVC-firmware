/**
 * spi.h
 * Written by Gerik Kubiak.
 *
 * Provides methods to use the ATmega's SPI bus. Currently not
 * thread safe.
**/

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "spi.h"

static const int mosi_pin = 2;
static const int miso_pin = 3;
static const int sck_pin = 1;
static const int ss_pin = 0; 

//TODO: Implement mutexes so the SPI library is thread safe.

/*
 * Initializes the SPI bus. Should be called before any other
 * SPI functions.
 */
void initializeSPI(){
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR1)|(1 << SPR0);
	DDRB |= (1 << ss_pin)|(1 << sck_pin)|(1 << mosi_pin);
	DDRB &= ~(1 << miso_pin);
	PORTB |= 1 << ss_pin;
	PORTB &= ~(1 << sck_pin);
}

/*
 * Sends one byte on the SPI bus. Does not return the result.
 *
 * unsigned char byte: The byte to send.
 */
void SPIsendByte(unsigned char byte){
	PORTB &= ~(1 << ss_pin);
	vTaskDelay(1);
	SPDR = byte;
	while((SPSR & (1 << SPIF)) == 0)
	;
	vTaskDelay(1);
	PORTB |= (1 << ss_pin);

}

/*
 * Sends two bytes on the SPI bus in big endian order. Does
 * not return the result.
 *
 * unsigned short data: The data to send.
 */
void SPIsendShort(unsigned short data){
	PORTB &= ~(1 << ss_pin);
	vTaskDelay(2);
	SPDR = (data >> 8);
	while((SPSR & (1 << SPIF)) == 0)
	;
	SPDR = data & 0xFF;
	while((SPSR & (1 << SPIF)) == 0)
	;
	vTaskDelay(2);
	PORTB |= (1 << ss_pin);
}

/*
 * Sends one byte without modifing the SS line. Allows
 * for custom protocols to be implemented. Returns
 * the byte read.
 *
 * unsigned char byte: The byte to send.
 * 
 * return: The byte read from the device on the SPI bus.
 */ 
unsigned char SPIsendByteNoSS(unsigned char byte){
   
   SPDR = byte;
   while((SPSR & (1 << SPIF)) == 0) vTaskDelay(1);
   return SPDR;
}

/*
 * Pull the SS line low.
 */
void enableSS(void) {
   PORTB &= ~(1 << ss_pin);
}

/*
 * Pull the SS line high.
 */
void disableSS(void) {
   PORTB |= (1 << ss_pin);
}
