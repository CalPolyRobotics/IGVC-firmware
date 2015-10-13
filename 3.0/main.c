#include "main.h"

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



  GPIO_InitTypeDef gpio;

  gpio.GPIO_Pin = GPIO_Pin_9;
  gpio.GPIO_Mode = GPIO_Mode_AF;
  gpio.GPIO_Speed = GPIO_Speed_10MHz;
  gpio.GPIO_OType = GPIO_OType_PP;
  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOA, &gpio);


  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);

  USART_InitTypeDef usart;

  usart.USART_BaudRate = 115200;
  usart.USART_WordLength = USART_WordLength_8b;
  usart.USART_StopBits = USART_StopBits_1;
  usart.USART_Parity = USART_Parity_No;
  usart.USART_Mode = USART_Mode_Tx;
  usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_Init(USART1, &usart);
  USART_Cmd(USART1, ENABLE);

  while (1)
  {
    if (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != RESET) // Check for Empty
      USART_SendData(USART1, 'T');
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

void Timer_Decrement()
{
    if (__timer > 0)
        __timer--;
} 

void assert_param(int x)
{

}
