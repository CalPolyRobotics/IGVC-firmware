/* USER CODE BEGIN (35) */
/*
_/ ____\___________
\   __\/    \_  __ \
 |  | |   |  \  | \/
 |__| |___|  /__|
           \/
 *
 *  Created on: Nov 25, 2014
 *      Author: Robotics
 * /*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <kkruse@calpoly.edu mrober15@calpoly.edu> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.  Kyle Kruse and Michael Roberts
 * ----------------------------------------------------------------------------
 */

#include "FreeRTOS.h"
#include "os_task.h"
#include"os_semphr.h"
/* USER CODE BEGIN (35) */
//! Init for the FNR Task starts up the Semaphores
/*!
\sa VtaskFNRINit()
*/
void VtaskFNRINit();
//! Task That is used performs operations on FNR. The Task will Block until a state has been changed.
/*!
\sa VTaskFNR(void *pvParameters)
\param void *pvParameters paramaters that are passed in during start up
*/
void VTaskFNR(void *pvParameters);

enum FNRSTATE
       {
	     NUETRAL,
         FORWARD,
         BACKWARD

       };
// the current state of the fnr
volatile  int FNRstate;
// locks the current state
SemaphoreHandle_t FNRMutex;
// tell the fnr task that the  fnr state has been set if this function fails to be updated over an x amount of time the fnr will be put into neatrul
SemaphoreHandle_t FNRUpdate;


/* USER CODE END */
