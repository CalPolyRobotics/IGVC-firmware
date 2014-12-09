/* USER CODE BEGIN (35) */

/*
          __                      .__
  _______/  |_  ____   ___________|__| ____    ____
 /  ___/\   __\/ __ \_/ __ \_  __ \  |/    \  / ___\
 \___ \  |  | \  ___/\  ___/|  | \/  |   |  \/ /_/  >
/____  > |__|  \___  >\___  >__|  |__|___|  /\___  /
     \/            \/     \/              \//_____/
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
//! Task That is used performs operations on FNR. The Task will Block until a state has been changed.
/*!
\sa void VtasksteeringiNit()
*/
void VtasksteeringiNit();
/*!
\sa void  VTasksteering(void *pvParameters)
\param  void *pvParameters paramerts that are being passed
*/
void VTasksteering(void *pvParameters);
volatile int targetval;

SemaphoreHandle_t targetvalMutex;
SemaphoreHandle_t targetvalUpdate;
SemaphoreHandle_t ADCbinarySEM;

volatile int tireloc;
SemaphoreHandle_t tirelocMutex;





/* USER CODE END */
