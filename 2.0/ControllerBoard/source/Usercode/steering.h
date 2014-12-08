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
 */
#include "FreeRTOS.h"
#include "os_task.h"
#include"os_semphr.h"

void VtasksteeringiNit();
void VTasksteering(void *pvParameters);
volatile int targetval;
SemaphoreHandle_t targetvalMutex;
SemaphoreHandle_t targetvalUpdate;
SemaphoreHandle_t ADCbinarySEM;

volatile int tireloc;
SemaphoreHandle_t tirelocMutex;





/* USER CODE END */
