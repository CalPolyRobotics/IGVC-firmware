#include "main.h"

#include "usart.h"
#include "utils/buffer8.h"
#include "comms.h"

#define PWM_GPIO GPIOC
#define PWM_GPIO_EN RCC_AHBENR_GPIOCEN
#define PWM_TIM_EN RCC_APB1ENR_TIM3EN
#define PWM_TIM TIM3
#define PWM_PERIOD_ARR 600
#define PWM_PERIOD_PSC 6000
#define PWM_DEFAULT_DUTY 2
#define CLOCK_SPEED 72000000

#define PWM_PACKET_LEN 1
#define PWM_MSG_TYPE 1

#define START_BYTE_1 'A'
#define START_BYTE_2 'B'

static uint16_t __timer = 0;

void Delay(uint16_t n)
{
    __timer = n;
    while (__timer > 0);
}

/*
void PWM_Init(GPIO_TypeDef* gpio, uint32_t rcc_ahbenr_gpioen,
              uint32_t rcc_apb1enr_timen, TIM_TypeDef* tim,
              uint32_t period, uint32_t duty)
{
    RCC->AHBENR |= rcc_ahbenr_gpioen;
    RCC->APB1ENR |= rcc_apb1enr_timen; // Enable Timer 3 clock
    // PC8 configuration
    gpio->MODER |= 2 << (8*2); // Alternate function mode
    gpio->OTYPER |= 0 << 8; // Output push-pull (reset state)
    gpio->OSPEEDR |= 0 << (8*2); // 2 MHz High speed
    gpio->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3
    // Period = 600*6000/72000000 = 50ms, Duty = Period / 2 = 25ms
    tim->PSC = period * CLOCK_SPEED / 600 / 1000; //5999; // Set prescaler to 6000 (PSC + 1)
    tim->ARR = 600; // Auto reload value 600
    tim->CCR3 = 600 / duty; // Start PWM duty for channel 3; Duty cycle is 1/denominator
    tim->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3
    tim->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
    tim->CR1 |= TIM_CR1_CEN; // Enable timer
}
*/

Packet_t PWM_MakePacket(uint8_t duty) {
    Packet_t packet = {0};

    packet.header.startByte[0] = START_BYTE_1;
    packet.header.startByte[1] = START_BYTE_2;
    packet.header.CRC8 = 0;
    packet.header.msgType = PWM_MSG_TYPE;
    packet.header.seqNumber = 0;
    packet.header.packetLen = PWM_PACKET_LEN;
    packet.data[0] = duty;

    return packet;
}

void PWM_Init(Packet_t* packet) {
    RCC->AHBENR |= PWM_GPIO_EN;
    RCC->APB1ENR |= PWM_TIM_EN; // Enable Timer 3 clock
    // PC8 configuration
    PWM_GPIO->MODER |= 2 << (8*2); // Alternate function mode
    PWM_GPIO->OTYPER |= 0 << 8; // Output push-pull (reset state)
    PWM_GPIO->OSPEEDR |= 0 << (8*2); // 2 MHz High speed
    PWM_GPIO->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3

    PWM_TIM->PSC = PWM_PERIOD_PSC;
    PWM_TIM->ARR = PWM_PERIOD_ARR;

    if (packet->data[0]) {
        PWM_TIM->CCR3 = PWM_PERIOD_ARR / packet->data[0];
    }
    else {
        PWM_TIM->CCR3 = PWM_PERIOD_ARR / PWM_DEFAULT_DUTY;
    }

    PWM_TIM->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3
    PWM_TIM->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
    PWM_TIM->CR1 |= TIM_CR1_CEN; // Enable timer
}

void PWM_Disable() {
   RCC->APB1ENR &= ~PWM_TIM_EN;
}

//Only use if pwm was already initialized
void PWM_Enable() {
   RCC->APB1ENR |= PWM_TIM_EN;
}

int main()
{

  RCC->AHBENR |= 0xFFFFFFFF;
  RCC->APB2ENR |= 0xFFFFFFFF;
  RCC->APB1ENR |= 0xFFFFFFFF;

  initIGVCUsart();

  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);

  STM_EVAL_LEDOff(LED6);
  STM_EVAL_LEDOff(LED7);

  SysTick_Config(SystemCoreClock / 1000);


  Packet_t pwm_packet = PWM_MakePacket(2);
  uint8_t* pwm_bytes = (uint8_t*) &pwm_packet;

/*
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable Timer 3 clock
  // PC8 configuration
  GPIOC->MODER |= 2 << (8*2); // Alternate function mode
  GPIOC->OTYPER |= 0 << 8; // Output push-pull (reset state)
  GPIOC->OSPEEDR |= 0 << (8*2); // 2 MHz High speed
  PIOC->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3
  // Period = 600*6000/72000000 = 50ms, Duty = Period / 2 = 25ms
  TIM3->PSC = 5999; // Set prescaler to 6000 (PSC + 1)
  TIM3->ARR = 600; // Auto reload value 600
  TIM3->CCR3 = 600/2; // Start PWM duty for channel 3; Duty cycle is 1/denominator
  TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3
  TIM3->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
  TIM3->CR1 |= TIM_CR1_CEN; // Enable timer

     while (1)
        ;
*/
  //TIM3->CCR3 = 600 / 4;
  /*printf("THIS IS A TEST\r\n");

  for (int i = 0; i < pwm_packet.header.packetLen; i++) {
    runCommsFSM(*pwm_bytes++);
  }
  while (1) {}
*/


  while (1)
  {
    if (usartHaveBytes())
    {
       runCommsFSM(usartGet());
    }
  } 

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

    //PWM_Init(GPIOC, RCC_AHBENR_GPIOCEN, RCC_APB1ENR_TIM3EN, TIM3, 50, 4);

 
     
 
 
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
        STM_EVAL_LEDToggle(LED10);
        Delay(500);
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
