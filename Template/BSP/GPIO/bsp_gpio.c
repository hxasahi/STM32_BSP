#include "bsp_gpio.h"

void GPIO_Config()
{
	GPIO_InitTypeDef  GPIO_Instruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_Instruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Instruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Instruct.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB,&GPIO_Instruct);
}
