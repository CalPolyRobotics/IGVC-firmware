/* USER CODE BEGIN (35) */
/*
                                          .__              .__  __
  ____  ____   _____   _____  __ __  ____ |__| ____ _____  |__|/  |_  ____   ____
_/ ___\/  _ \ /     \ /     \|  |  \/    \|  |/ ___\\__  \ |  \   __\/  _ \ /    \
\  \__(  <_> )  Y Y  \  Y Y  \  |  /   |  \  \  \___ / __ \|  ||  | (  <_> )   |  \
 \___  >____/|__|_|  /__|_|  /____/|___|  /__|\___  >____  /__||__|  \____/|___|  /
     \/            \/      \/           \/        \/     \/                     \/
 *
 *  Created on: Nov 25, 2014
 *      Author: Robotics
 */

#include "communication.h"


void VTaskCommuncation(void *pvParameters)
{
    xSemaphore = xSemaphoreCreateBinary();

    for(;;)
    {
        /* Taggle HET[1] with timer tick */
        gioSetBit(hetPORT1, 17, gioGetBit(hetPORT1, 17) ^ 1);
        vTaskDelay(100);
    }   
}



/* USER CODE END */
