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
#include "steering.h"
#include  "global.h"
#include "gio"

void VTasksteering(void *pvParameters)
{
    xSemaphore = xSemaphoreCreateBinary();

    for(;;)
    {
        /* Taggle HET[1] with timer tick */

    	//locktirelocmutex
    		// get latested tirloc
    	// unlocktireloc mutex
    	if(  ( targetval - tireloc) < 0 )
    	{
    		gioSetBit(gioPORTA,1 < STEERINGMDIRPIN,0)

    	}
    	else
    	{
    		gioSetBit(gioPORTA,1 < STEERINGMDIRPIN,1)


    	}
    	pwmSetDuty(hetRAM1,STEERINGPWM , STEERINGK*( targetval - tireloc) % 100))

    	vTaskDelay(100);
    }
}




/* USER CODE END */
