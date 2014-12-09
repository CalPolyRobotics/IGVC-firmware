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
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <kkruse@calpoly.edu mrober15@calpoly.edu> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.  Kyle Kruse and Michael Roberts
 * ----------------------------------------------------------------------------
 */

#include "gio.h"
#include "global.h"
#include "het.h"
#include "fnr.h"
//! Init for the FNR Task starts up the Semaphores
/*!
\sa VtaskFNRINit()
*/
void VtaskFNRINit()
{
	FNRMutex = xSemaphoreCreateMutex();
    vSemaphoreCreateBinary(FNRUpdate);
    gioSetBit(hetPORT1, FNRENABLE, 0XFF);
    gioSetBit(hetPORT1, FNRDIR, 0);
    FNRstate= NUETRAL;
}

//! Task That is used performs operations on FNR. The Task will Block until a state has been changed.
/*!
\sa VTaskFNR(void *pvParameters)
\param void *pvParameters paramaters that are passed in during start up
*/
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
