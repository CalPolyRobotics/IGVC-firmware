/***************************
*
* Filename: usart.h
*
* Description: Provides print methods for various
*  datatypes using USART.
*
* Authors: Doug Gallatin and Jason Schray
*
***************************/


#ifndef USART_H_
#define USART_H_

#define CURR_USART 0

#define UDRN_HELP2(x) UDR ## x
#define UDRN_HELP(x) UDRN_HELP2(x)
#define UDRN UDRN_HELP(CURR_USART)

#define UCSRNA_HELP2(x) UCSR ## x ## A
#define UCSRNA_HELP(x) UCSRNA_HELP2(x)
#define UCSRNA UCSRNA_HELP(CURR_USART)

#define UCSRNB_HELP2(x) UCSR ## x ## B
#define UCSRNB_HELP(x) UCSRNB_HELP2(x)
#define UCSRNB UCSRNB_HELP(CURR_USART)

#define UCSRNC_HELP2(x) UCSR ## x ## C
#define UCSRNC_HELP(x) UCSRNC_HELP2(x)
#define UCSRNC UCSRNC_HELP(CURR_USART)

#define UBRRNL_HELP2(x) UBRR ## x ## L
#define UBRRNL_HELP(x) UBRRNL_HELP2(x)
#define UBRRNL UBRRNL_HELP(CURR_USART)

#define UBRRNH_HELP2(x) UBRR ## x ## H
#define UBRRNH_HELP(x) UBRRNH_HELP2(x)
#define UBRRNH UBRRNH_HELP(CURR_USART)

#define USARTN_RX_HELP2(x) USART ## x ## _RX_vect
#define USARTN_RX_HELP(x) USARTN_RX_HELP2(x)
#define USARTN_RX_vect USARTN_RX_HELP(CURR_USART)

#define USARTN_TX_HELP2(x) USART ## x ## _TX_vect
#define USARTN_TX_HELP(x) USARTN_TX_HELP2(x)
#define USARTN_TX_vect USARTN_TX_HELP(CURR_USART)


void initializeUSART(void);

void USARTQueueVar(char data);
void USARTQueueBuf(char *buf, int size);
void printHex(int i);
void printNum(unsigned int i);

#endif /* USART_H_ */
