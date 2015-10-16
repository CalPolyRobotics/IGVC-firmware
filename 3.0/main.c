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
  STM_EVAL_LEDInit(LED5);

  SysTick_Config(SystemCoreClock / 1000);

  while(1)
  {
    uint32_t bytes;
    uint8_t data[32];
    if ((bytes = usartHaveBytes()) > 5)
    {
      usartRead(data, bytes);
      usartWrite(data, bytes);
    }
  }

  while(1)
  {
    usartPrint("STM32\r\n");
    //usartPut('1');
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

    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable Timer 3 clock
    // PC8 configuration
    GPIOC->MODER |= 2 << (8*2); // Alternate function mode
    GPIOC->OTYPER |= 0 << 8; // Output push-pull (reset state)
    GPIOC->OSPEEDR |= 0 << (8*2); // 2 MHz High speed
    GPIOC->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3
    // Period = 600*6000/72000000 = 50ms, Duty = Period / 2 = 25ms
    TIM3->PSC = 5999; // Set prescaler to 6000 (PSC + 1)
    TIM3->ARR = 600; // Auto reload value 600
    TIM3->CCR3 = 600/2; // Start PWM duty for channel 3; Duty cycle is 1/denominator
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3
    TIM3->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
    TIM3->CR1 |= TIM_CR1_CEN; // Enable timer

    while (1) {
        GPIO_SetBits(GPIOA, GPIO_Pin_9);
        /*STM_EVAL_LEDToggle(LED3);
        STM_EVAL_LEDToggle(LED4);
        STM_EVAL_LEDToggle(LED5);
        STM_EVAL_LEDToggle(LED6);
        STM_EVAL_LEDToggle(LED7);
        STM_EVAL_LEDToggle(LED8);
        STM_EVAL_LEDToggle(LED9);
        */
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
