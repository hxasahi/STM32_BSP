#include "stm32f10x.h"   
#include "bsp_debug.h"
#include "bsp_delay.h"
#include "bsp_SysTick.h"

int main(void)
{
	DEBUG_Config();	
	SysTick_Init();
	while(1)
	{
		printf("demo");
		Delay_ms(1000);
	}
}
