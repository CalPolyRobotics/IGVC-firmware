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

void VTaskthrottle(void *pvParameters);

volatile  int throttlelevel ;
// locks the current state
SemaphoreHandle_t throttlevelmutex;
// tell the fnr task to update the throttle level if the throttle level fails to be updated for a x amount of time  the throttle will go to zero
SemaphoreHandle_t throttlelevelupdate;




/* USER CODE END */
