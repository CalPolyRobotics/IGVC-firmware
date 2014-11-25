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
 */

/* USER CODE BEGIN (35) */

void VTaskFNR(void *pvParameters);
enum FNRSTATE
       {
	     NUETRAL,
         FORWARD,
         BACKWARD

       };
// the current state of the fnr
volatile  FNRSTATE state;
// locks the current state
SemaphoreHandle_t FNRMutex;
// tell the fnr task that the  fnr state has been set if this function fails to be updated over an x amount of time the fnr will be put into neatrul
SemaphoreHandle_t FNRUpdate;


/* USER CODE END */
