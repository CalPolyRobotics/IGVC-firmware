#include "main.h"

#define CLOCK_SPEED 72000000

static uint16_t __timer = 0;

void Delay(uint16_t n)
{
    __timer = n;
    while (__timer > 0);
}

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



int main()
{
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    STM_EVAL_LEDInit(LED7);
    STM_EVAL_LEDInit(LED8);
    STM_EVAL_LEDInit(LED9);
    STM_EVAL_LEDInit(LED10);

    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        while (1);
    }

    PWM_Init(GPIOC, RCC_AHBENR_GPIOCEN, RCC_APB1ENR_TIM3EN, TIM3, 50, 4);
/*
 *
 *    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
 *    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable Timer 3 clock
 *    // PC8 configuration
 *    GPIOC->MODER |= 2 << (8*2); // Alternate function mode
 *    GPIOC->OTYPER |= 0 << 8; // Output push-pull (reset state)
 *    GPIOC->OSPEEDR |= 0 << (8*2); // 2 MHz High speed
 *    GPIOC->AFR[1] |= 2 << ((8-8)*4); // Select AF2 for PC8: TIM3_CH3
 *    // Period = 600*6000/72000000 = 50ms, Duty = Period / 2 = 25ms
 *    TIM3->PSC = 5999; // Set prescaler to 6000 (PSC + 1)
 *    TIM3->ARR = 600; // Auto reload value 600
 *    TIM3->CCR3 = 600/2; // Start PWM duty for channel 3; Duty cycle is 1/denominator
 *    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 on channel 3
 *    TIM3->CCER |= TIM_CCER_CC3E; // Enable compare on channel 3
 *    TIM3->CR1 |= TIM_CR1_CEN; // Enable timer
 *
 */
    while (1) {
        STM_EVAL_LEDToggle(LED3);
        STM_EVAL_LEDToggle(LED4);
        STM_EVAL_LEDToggle(LED5);
        STM_EVAL_LEDToggle(LED6);
        STM_EVAL_LEDToggle(LED7);
        STM_EVAL_LEDToggle(LED8);
        STM_EVAL_LEDToggle(LED9);
        STM_EVAL_LEDToggle(LED10);
        Delay(500);
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
