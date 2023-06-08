#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_debug.h"
#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_dht11.h"
#include "core_delay.h"
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "bsp_color_led.h"

static void AppTaskCreate(void *arg);
static void Key_Task(void *parameter);
static void Test_Task(void *parameter);
static void ADC_Task(void *arg);
static void LED_Task(void *arg);
static TaskHandle_t AppTaskCreateHandle = NULL;
static TaskHandle_t Key_Task_Handle = NULL;
static TaskHandle_t Test_Task_Handle = NULL;
static TaskHandle_t ADC_Task_Handle = NULL;
static TaskHandle_t LED_Task_Handle = NULL;
int main(void)
{
    BaseType_t xReturn = pdPASS;
    DEBUG_Config();
#if USE_KEY
    KEY_Init();    
#endif  //USE_KEY   
    DHT11_Init();
	ADCx_Init();
	//GPIO_Config();
	COLOR_TIMx_LED_Init();
    printf("FreeRTOS\r\n");
    xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                          (const char *)"AppTaskCreate",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&AppTaskCreateHandle);

    if (pdPASS == xReturn)
        vTaskStartScheduler();
    else
        return -1;
    while (1);
}
static void AppTaskCreate(void *arg)
{
    BaseType_t xReturn = pdPASS;
    taskENTER_CRITICAL();
    xReturn = xTaskCreate((TaskFunction_t)Key_Task,
                          (const char *)"KeyTask",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&Key_Task_Handle);
    if (xReturn == pdPASS)
        printf("创建Key_Task成功\r\n");
    xReturn = xTaskCreate((TaskFunction_t)Test_Task,
                          (const char *)"TestTask",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&Test_Task_Handle);
    if (xReturn == pdPASS)
        printf("创建Test_Task成功\r\n");
	xReturn = xTaskCreate((TaskFunction_t)ADC_Task,
						  (const char *)"ADCTask",
					      (uint16_t)512,
						  (void *)NULL,
						  (UBaseType_t)1,
						  (TaskHandle_t *)&ADC_Task_Handle);
	if(xReturn == pdPASS)
		printf("创建ADC_Task成功\r\n");
	xReturn = xTaskCreate((TaskFunction_t)LED_Task,
						  (const char *)"LEDTask",
					      (uint16_t)512,
						  (void *)NULL,
						  (UBaseType_t)1,
						  (TaskHandle_t *)&LED_Task_Handle);
	if(xReturn == pdPASS)
		printf("创建LED_Task成功\r\n");
    vTaskDelete(AppTaskCreateHandle);
    taskEXIT_CRITICAL();
}
static void Key_Task(void *parameter)
{
    uint8_t keycode;
    while (1)
    {
#if USE_KEY
        keycode = KEY_FIFO_Get();
        if (keycode != KEY_NONE)
        {
            switch (keycode)
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
        vTaskDelay(2);
#endif  //USE_KEY       
    }
}
static void Test_Task(void *parameter)
{
    DHT11_Data_TypeDef DHT11_Data;
    while (1)
    {
        printf("1\r\n");        
		vTaskSuspendAll();		
        /*调用DHT11_Read_TempAndHumidity读取温湿度，若成功则输出该信息*/
        if (DHT11_Read_TempAndHumidity(& DHT11_Data) == SUCCESS)
        {			
            printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n", \
                   DHT11_Data.humi_int, DHT11_Data.humi_deci, DHT11_Data.temp_int, DHT11_Data.temp_deci);
        }
        else
        {
            printf("Read DHT11 ERROR!\r\n");
        }
		xTaskResumeAll();
        vTaskDelay(2000);
    }
}
static void ADC_Task(void *arg)
{
	extern __IO uint16_t ADC_ConvertedValue;
	float ADC_ConvertedValueLocal; 
	while (1)
	{		
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 		
		vTaskDelay(1000);
	}
}
static void LED_Task(void *arg)
{
	uint16_t time = 30;
	uint32_t color = 0;	
	uint8_t flag = 0;
	while(1)
	{		
		SetRGBColor(color);
		vTaskDelay(time);			
		if(!flag)
		{
			color = color + 0x111111;			
		}
		else
		{
			color = color - 0x111111;			
		}
		if(color == 0xffffff && flag == 0)	
			flag = 1;		
		if(color == 0 && flag == 1)
			flag = 0;
	}
}
