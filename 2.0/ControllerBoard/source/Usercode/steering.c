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
#include "gio.h"
#include "het.h"
#include "adc.h"
void adcNotification(adcBASE_t *adc, uint32 group)
{
	if(adcGROUP1 == group)
	{
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(ADCbinarySEM,&xHigherPriorityTaskWoken);


	}
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (11) */
/* USER CODE END */
}

void VtasksteeringiNit()
{
    vSemaphoreCreateBinary(ADCbinarySEM);

    adcInit();
    adcEnableNotification(adcREG1,adcGROUP1);
	targetvalMutex = xSemaphoreCreateMutex();
	tirelocMutex = xSemaphoreCreateMutex();
    vSemaphoreCreateBinary(targetvalUpdate);
    vSemaphoreCreateBinary(ADCbinarySEM);

    gioSetBit(gioPORTA,  STEERINGMDIRPIN, 0XFF);
    gioSetDirection(gioPORTA, 1<STEERINGMDIRPIN);

    tireloc = 0xdead;
    targetval = 2893;
    pwmStart(hetRAM1,STEERINGPWM);

}
adcData_t adc_data[24];

void VTasksteering(void *pvParameters)
{

    for(;;)
    {
    	adcStartConversion(adcREG1, adcGROUP1);
        xSemaphoreTake(ADCbinarySEM, portMAX_DELAY);
        /* Taggle HET[1] with timer tick */
    	xSemaphoreTake(tirelocMutex, portMAX_DELAY);
       adcGetData(adcREG1, adcGROUP1,&adc_data[0]);
       tireloc= adc_data[0].value;
    	xSemaphoreGive(tirelocMutex);
    	//locktirelocmutex
    		// get latested tirloc
    	// unlocktireloc mutex
    	xSemaphoreTake(targetvalMutex, portMAX_DELAY);

    	if(  ( targetval - tireloc) < 0 )
    	{
    		gioSetBit(gioPORTA, STEERINGMDIRPIN,0);

    	}
    	else
    	{
    		gioSetBit(gioPORTA,STEERINGMDIRPIN,1);


    	}
    	float  a = ((((float)( targetval - tireloc))/3900)*100);
    	pwmSetDuty(hetRAM1,STEERINGPWM ,(int) a );
        xSemaphoreGive(targetvalMutex);

    	vTaskDelay(100);
    }
}




/* USER CODE END */
