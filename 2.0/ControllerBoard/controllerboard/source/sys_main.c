/** @file sys_main.c 
*   @brief Application main file
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "sys_common.h"

#include "sys_common.h"
#include "system.h"

/* Include FreeRTOS scheduler files */
#include "FreeRTOS.h"
#include "os_task.h"

/* Include HET header file - types, definitions and function declarations for system driver */
#include "het.h"
#include "esm.h"
#include "sci.h"
#include "sys_common.h"
#include "system.h"
#include "spi.h"
#include "het.h"
#include "can.h"
#include "esm.h"
#include "sys_core.h"
#include "communication.h"
#include "fnr.h"
#include "steering.h"
#include "gio.h"
#define  TSIZE1 10
uint8  TEXT1[TSIZE1]= {'H','E','R','C','U','L','E','S',' ',' '};
#define  TSIZE2 18
uint8  TEXT2[TSIZE2]= {'M','I','C','R','O','C','O','N','T','R','O','L','L','E','R','S',' ',' '};
#define  TSIZE3 19
uint8  TEXT3[TSIZE3]= {'T','E','X','A','S',' ','I','N','S','T','R','U','M','E','N','T','S','\n','\r'};

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void wait(uint32 time);


#define UART scilinREG
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void vTask1(void *pvParameters)
{
    for(;;)
    {
        /* Taggle HET[1] with timer tick */
        gioSetBit(hetPORT1, 8, gioGetBit(hetPORT1, 8) ^ 1);
        vTaskDelay(10000);
    }
}
/* USER CODE END */

void main(void)
                    {
/* USER CODE BEGIN (3) */
    _enable_interrupt_();
    hetInit();

    sciInit();      /* initialize sci/sci-lin    */
                    /* even parity , 2 stop bits */
    sciEnableNotification(UART,SCI_RX_INT);

    xTaskHandle xTask1Handle;
    xTaskHandle xTask2Handle;
    xTaskHandle xTask3Handle;
    xTaskHandle xTask4Handle;
    xTaskHandle xTask5Handle;
    xTaskHandle xTask6Handle;


    gioSetDirection(hetPORT1, 0xFFFFFFFF&~(1<<22));
    comsetup();
    if (xTaskCreate(vTask1,"Tadsk1", configMINIMAL_STACK_SIZE, NULL, 1, &xTask4Handle) != pdTRUE)
    {
        /* Task could not be created */
        while(1);
    }

    if (xTaskCreate(communicationTxtask,"Task1", configMINIMAL_STACK_SIZE+50, NULL, 1, &xTask1Handle) != pdTRUE)
    {
        while(1);
    }

    if (xTaskCreate(communicationRxtask,"Task2", configMINIMAL_STACK_SIZE+50, NULL, 1, &xTask2Handle) != pdTRUE)
     {
         while(1);
     }

    if (xTaskCreate(VTaskCommuncation,"Task3", configMINIMAL_STACK_SIZE+50, NULL, 1, &xTask3Handle) != pdTRUE)
     {
         while(1);
     }
     VtaskFNRINit();
     if (xTaskCreate(VTaskFNR,"Task5", configMINIMAL_STACK_SIZE+50, NULL, 1, &xTask5Handle) != pdTRUE)
       {
           while(1);
       }
     VtasksteeringiNit();
     if (xTaskCreate(VTasksteering,"Task6", configMINIMAL_STACK_SIZE+50, NULL, 1, &xTask6Handle) != pdTRUE)
        {
            while(1);
        }
    /* Start Scheduler */
    vTaskStartScheduler();

    while(1);



     int i = 0;


/* USER CODE END */
}

/* USER CODE BEGIN (4) */
void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((UART->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(UART,*text++);      /* send out text   */
    };
}


void wait(uint32 time)
{
    time--;
}
/* USER CODE END */
