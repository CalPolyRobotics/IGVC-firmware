/*
*
*
*
*/ 

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f30x.h"
#include "stm32f30x_it.h"
#include "stm32f3_discovery.h"

#include "comms.h"

void Timer_Decrement();
void PWM_Init(Packet_t* packet);

#endif
