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
#include "gio.h"
#include "global.h"
#include "het.h"
#include "fnr.h"
void VtaskFNRINit()
{
	FNRMutex = xSemaphoreCreateMutex();
    vSemaphoreCreateBinary(FNRUpdate);
    gioSetBit(hetPORT1, FNRENABLE, 0XFF);
    gioSetBit(hetPORT1, FNRDIR, 0);
    FNRstate= NUETRAL;
}

void VTaskFNR(void *pvParameters)
{

    for(;;)
    {
    	xSemaphoreTake(FNRMutex, portMAX_DELAY);
    	if(FNRstate== NUETRAL)
    	{
        gioSetBit(hetPORT1, FNRENABLE, 0XFF);
        gioSetBit(hetPORT1, FNRDIR, 0);
    	}
    	else if(FNRstate== FORWARD)
    	{
        gioSetBit(hetPORT1, FNRENABLE, 0);
    	gioSetBit(hetPORT1, FNRDIR, 0);
    	}
    	else if(FNRstate== BACKWARD)
    	{
        gioSetBit(hetPORT1, FNRENABLE, 0);
        gioSetBit(hetPORT1, FNRDIR, 0xff);
        }

        xSemaphoreGive(FNRMutex);
    	xSemaphoreTake(FNRUpdate, portMAX_DELAY);




    }
}






/* USER CODE END */
