#include "main.h"

#include "usart.h"
#include "utils/buffer8.h"

static uint16_t __timer = 0;

void Delay(uint16_t n)
{
    __timer = n;
    while (__timer > 0);
}

int main()
{

  RCC->AHBENR |= 0xFFFFFFFF;
  RCC->APB2ENR |= 0xFFFFFFFF;
  RCC->APB1ENR |= 0xFFFFFFFF;

  initIGVCUsart();

  STM_EVAL_LEDInit(LED4);

  SysTick_Config(SystemCoreClock / 1000);



  while(1)
  {
    usartWrite("Hello World!!!\r\n", 4);
    //usartPut('1');
    STM_EVAL_LEDToggle(LED4);
    Delay(100);
  }


  while (1)
  {
    uint16_t data;
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
      data = USART_ReceiveData(USART1);

      //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
      USART_SendData(USART1, data);
    }


  }


  GPIO_SetBits(GPIOA, GPIO_Pin_9);




    /*STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    STM_EVAL_LEDInit(LED7);
    STM_EVAL_LEDInit(LED8);
    STM_EVAL_LEDInit(LED9);
    STM_EVAL_LEDInit(LED10);*/

    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        while (1);
    }

    while (1) {
        GPIO_SetBits(GPIOA, GPIO_Pin_9);
        /*STM_EVAL_LEDToggle(LED3);
        STM_EVAL_LEDToggle(LED4);
        STM_EVAL_LEDToggle(LED5);
        STM_EVAL_LEDToggle(LED6);
        STM_EVAL_LEDToggle(LED7);
        STM_EVAL_LEDToggle(LED8);
        STM_EVAL_LEDToggle(LED9);
        STM_EVAL_LEDToggle(LED10);*/
        Delay(100);
        GPIO_ResetBits(GPIOA, GPIO_Pin_9);
        Delay(100);
    }
}

/*void USART1_IRQHandler()
{
  uint16_t data;
  data = USART_ReceiveData(USART1);

  USART_SendData(USART1, data + 1);
}*/

void Timer_Decrement()
{
    if (__timer > 0)
        __timer--;
} 

void assert_param(int x)
{

}
