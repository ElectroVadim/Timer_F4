#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"




void TIM4_IRQHandler(void) {
if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
GPIOD->ODR ^= GPIO_Pin_15;
	}
}

void TIM2_IRQHandler(void) {
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
GPIOD->ODR ^= GPIO_Pin_13;
	}
}


//------------------------------------
void GPIO_Config(void);
//------------------------------------
void INTTIM4_Config(void);
//------------------------------------
void INTTIM2_Config(void);
//------------------------------------
void init_Button(void);
void init_LED(void);
void delay(uint16_t a);

int main(void)
{

	GPIO_Config();
	INTTIM4_Config();
	INTTIM2_Config();
 while(1)
 {


 }
}

void GPIO_Config(void){
GPIO_InitTypeDef gpio_struct;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
gpio_struct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13 ;
gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
gpio_struct.GPIO_OType = GPIO_OType_PP;
gpio_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOD, &gpio_struct);
}

void INTTIM4_Config(void)
{
NVIC_InitTypeDef nvic_struct;
nvic_struct.NVIC_IRQChannel = TIM4_IRQn;
nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
nvic_struct.NVIC_IRQChannelSubPriority = 1;
nvic_struct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&nvic_struct);
TIM_TimeBaseInitTypeDef tim_struct;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
tim_struct.TIM_Period = 20000 - 1;
tim_struct.TIM_Prescaler = 1500 - 1;
tim_struct.TIM_ClockDivision = 0;
tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM4, &tim_struct);
TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
TIM_Cmd(TIM4, ENABLE);
}


void INTTIM2_Config(void)
{
NVIC_InitTypeDef nvic_struct;
nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
nvic_struct.NVIC_IRQChannelSubPriority = 1;
nvic_struct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&nvic_struct);
TIM_TimeBaseInitTypeDef tim_struct;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
tim_struct.TIM_Period = 20000 - 1;
tim_struct.TIM_Prescaler = 250 - 1;
tim_struct.TIM_ClockDivision = 0;
tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM2, &tim_struct);
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
TIM_Cmd(TIM2, ENABLE);
}

