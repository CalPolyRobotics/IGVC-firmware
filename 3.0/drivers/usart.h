#ifndef __USART_H__
#define __USART_H__

#include <stdint.h>

void initIGVCUsart();
void usartPut(uint8_t data);
void usartWrite(uint8_t* data, uint32_t size);
void usartPrint(char* data);


#endif