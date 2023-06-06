#include "stm32f10x.h"   
#include "bsp_debug.h"
#include "bsp_delay.h"
#include "bsp_SysTick.h"
#include "bsp_key.h"

int main(void)
{	
	uint8_t keycode;
	DEBUG_Config();	
	SysTick_Init();
	KEY_Init();
	printf("key\r\n");
	while(1)
	{
		keycode=KEY_FIFO_Get();
		if(keycode != KEY_NONE)
		{
			switch(keycode)
			{
				case KEY_1_DOWN:
					printf("key1 down\r\n");
					break;				
				case KEY_1_LONG:
					printf("key1 long\r\n");
					break;
				case KEY_2_DOWN:
					printf("key2 down\r\n");
					break;
				case KEY_2_LONG:
					printf("key2 long\r\n");
					break;
				default:
					;									
			}
		}		
	}
}
