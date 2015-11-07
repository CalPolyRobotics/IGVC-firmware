#include "main.h"
#include <stdio.h>
#include "usart.h"
#include "utils/buffer8.h"
static uint16_t __timer = 0; 
void Delay(uint16_t n)
{
    __timer = n;
    while (__timer > 0);
}

void IGVC_I2C(){

   GPIO_InitTypeDef gpio;

   gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
   gpio.GPIO_Mode = GPIO_Mode_AF;
   gpio.GPIO_Speed = GPIO_Speed_10MHz;
   gpio.GPIO_OType = GPIO_OType_OD;
   gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

   GPIO_Init(GPIOB, &gpio);


   GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_4);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_4);

   I2C_InitTypeDef i2c;
   i2c.I2C_Timing = (1<<28)|(4<<20)|(2<<16)|(0xC3<<8)|(0xC7<<0); //default 10kHz timing

   i2c.I2C_AnalogFilter = I2C_AnalogFilter_Disable;
   i2c.I2C_DigitalFilter = 0;
   i2c.I2C_Mode = I2C_Mode_I2C;
   i2c.I2C_OwnAddress1 = 0; // I'm confused as to what this signifies
   i2c.I2C_Ack = I2C_Ack_Enable;
   i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

   I2C_Init(I2C1,&i2c);
   I2C_MasterRequestConfig(I2C1, I2C_Direction_Transmitter);
   I2C_Cmd(I2C1, ENABLE);

}


void I2C_read_register(uint8_t address, uint8_t regnum, uint8_t *data, uint8_t length){
   I2C_TransferHandling(I2C1, address, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write); 
   while(!(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == SET));
   I2C_SendData(I2C1, regnum);
   I2C_TransferHandling(I2C1, address, length, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
   while(length > 0){ 
      *data = I2C_ReceiveData(I2C1);
      printf("Received Data from %X register %X: %X\r\n",address,regnum, *data); 
      length--;
   }
   printf("Generating stop bit \n");
    
   I2C_TransferHandling(I2C1, address, 0, I2C_AutoEnd_Mode, I2C_Generate_Stop);
}

void I2C_write_register(uint8_t address, uint8_t *data){
    

}



int main()
{

  RCC->AHBENR |= 0xFFFFFFFF;
  RCC->APB2ENR |= 0xFFFFFFFF;
  RCC->APB1ENR |= 0xFFFFFFFF;


  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);

  SysTick_Config(SystemCoreClock / 1000);



  
   IGVC_I2C();
    	   
   initIGVCUsart();
   uint8_t I2C_write_address = 0x28;
   uint8_t data = 0; 
  
   while(1){
      I2C_read_register(0x33, I2C_write_address, &data, 2);   
//      while(!(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == SET));
      printf("Data received: %X\r\n", data);
      
//      I2C_TransferHandling(I2C1, I2C_write_address, 1, I2C_AutoEnd_Mode, I2C_Generate_Stop);
//      Delay(50);
   }
   uint8_t __address = 0x22; 
   uint8_t pass = 0;
   while(1)

   {
     printf("Initializing WRITE\n");      
     Delay(50);
     I2C_TransferHandling(I2C1, 0x33, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);    
     if(pass == 0){ 
        while(!(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == SET));
     }
     printf("Writing to address %X\r\n", __address); 
     I2C_SendData(I2C1, __address);
     I2C_TransferHandling(I2C1, 0x33, 1, I2C_AutoEnd_Mode, I2C_Generate_Stop);  
     I2C_TransferHandling(I2C1, 0x33, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
     printf("Received Data: %X\r\n", I2C_ReceiveData(I2C1));
     I2C_TransferHandling(I2C1, 0x33, 1, I2C_AutoEnd_Mode, I2C_Generate_Stop); 
     //while(!(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == SET));
/*     I2C_TransferHandling(I2C1, 0x3D, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read); 
     printf("Attempting to read from Magnetic Field Digital Interface \n");
     Delay(50);
     printf("Received Data from magnetic field interface: %X\r\n", I2C_ReceiveData(I2C1));
     I2C_TransferHandling(I2C1, 0x3D, 1, I2C_AutoEnd_Mode, I2C_Generate_Stop);*/
     if(pass == 0){
        pass = 1;
     }
     Delay(50);
   }
  



	




  while (1)
  {
     printf("Hello Newlib!\r\n");
     Delay(100);
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
