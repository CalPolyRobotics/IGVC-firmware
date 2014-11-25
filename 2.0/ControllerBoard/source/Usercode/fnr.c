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

void VTaskFNR(void *pvParameters)
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
