/* USER CODE BEGIN (35) */

/*
  __  .__                  __    __  .__
_/  |_|  |_________  _____/  |__/  |_|  |   ____
\   __\  |  \_  __ \/  _ \   __\   __\  | _/ __ \
 |  | |   Y  \  | \(  <_> )  |  |  | |  |_\  ___/
 |__| |___|  /__|   \____/|__|  |__| |____/\___  >
           \/                                  \/
 *
 *  Created on: Nov 25, 2014
 *      Author: Robotics
 */
void VTaskthrottle(void *pvParameters)
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
