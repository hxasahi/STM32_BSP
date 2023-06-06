#include "stm32f10x.h"   
#include "bsp_debug.h"
#include "bsp_key.h"
#include "FreeRTOS.h"
#include "task.h"
static void Key_Task(void* parameter);
static void Test_Task(void* parameter);
static TaskHandle_t Key_Task_Handle = NULL;
static TaskHandle_t Test_Task_Handle = NULL;
int main(void)
{		
	BaseType_t xReturn1 = pdPASS;
	BaseType_t xReturn2 = pdPASS;
	DEBUG_Config();		
#if USE_KEY	
	KEY_Init();	
#endif  //USE_KEY	
	printf("key\r\n");
	xReturn1 = xTaskCreate((TaskFunction_t)Key_Task,
							(const char*)"KeyTask",
							(uint16_t)512,
							(void*)NULL,
							(UBaseType_t)1,
							(TaskHandle_t*)&Key_Task_Handle);
							
	xReturn2 = xTaskCreate((TaskFunction_t)Test_Task,
							(const char*)"TestTask",
							(uint16_t)512,
							(void*)NULL,
							(UBaseType_t)1,
							(TaskHandle_t*)&Test_Task_Handle);
	if(pdPASS == xReturn1 && pdPASS == xReturn2)
		vTaskStartScheduler();
	else
		return -1;
	while(1);
}
static void Key_Task(void* parameter)
{
	uint8_t keycode;
	while(1)
	{
#if USE_KEY		
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
#endif  //USE_KEY		
	}
}
static void Test_Task(void* parameter)
{
	while(1)
	{
		printf("1\r\n");
		vTaskDelay(1000);
	}
}
