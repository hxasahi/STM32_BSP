#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp_debug.h"
#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_dht11.h"
#include "core_delay.h"
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "bsp_color_led.h"

uint8_t StartFlag = 0;
extern uint32_t time5s;
static void AppTaskCreate(void *arg);
static void Key_Task(void *parameter);
static void Test_Task(void *parameter);
static void ADC_Task(void *arg);
static void LED_Task(void *arg);
static void TIME_Task(void *arg);
static TaskHandle_t AppTaskCreateHandle = NULL;
static TaskHandle_t Key_Task_Handle = NULL;
static TaskHandle_t Test_Task_Handle = NULL;
static TaskHandle_t ADC_Task_Handle = NULL;
static TaskHandle_t LED_Task_Handle = NULL;
static TaskHandle_t TIME_Task_Handle = NULL;
QueueHandle_t Test_Queue = NULL;
#define QUEUE_LEN 4
#define QUEUE_SIZE 1
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
	Test_Queue = xQueueCreate((UBaseType_t)QUEUE_LEN,
							  (UBaseType_t)QUEUE_SIZE);
	if(Test_Queue != NULL)
		printf("����Test_Queue��Ϣ���гɹ�\r\n");    
    xReturn = xTaskCreate((TaskFunction_t)Key_Task,
                          (const char *)"KeyTask",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&Key_Task_Handle);
    if (xReturn == pdPASS)
        printf("����Key_Task�ɹ�\r\n");
    xReturn = xTaskCreate((TaskFunction_t)Test_Task,
                          (const char *)"TestTask",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&Test_Task_Handle);
    if (xReturn == pdPASS)
        printf("����Test_Task�ɹ�\r\n");
	xReturn = xTaskCreate((TaskFunction_t)ADC_Task,
						  (const char *)"ADCTask",
					      (uint16_t)512,
						  (void *)NULL,
						  (UBaseType_t)1,
						  (TaskHandle_t *)&ADC_Task_Handle);
	if(xReturn == pdPASS)
		printf("����ADC_Task�ɹ�\r\n");
	xReturn = xTaskCreate((TaskFunction_t)LED_Task,
						  (const char *)"LEDTask",
					      (uint16_t)512,
						  (void *)NULL,
						  (UBaseType_t)1,
						  (TaskHandle_t *)&LED_Task_Handle);
	if(xReturn == pdPASS)
		printf("����LED_Task�ɹ�\r\n");
	xReturn = xTaskCreate((TaskFunction_t)TIME_Task,
						  (const char *)"TIMETask",
					      (uint16_t)512,
						  (void *)NULL,
						  (UBaseType_t)1,
						  (TaskHandle_t *)&TIME_Task_Handle);
	if(xReturn == pdPASS)
		printf("����TIME_Task�ɹ�\r\n");
    vTaskDelete(AppTaskCreateHandle);
    taskEXIT_CRITICAL();
}
static void Key_Task(void *parameter)
{
    uint8_t keycode;
	BaseType_t xReturn = pdPASS;
    while (1)
    {
#if USE_KEY
        keycode = KEY_FIFO_Get();
        if (keycode != KEY_NONE)
        {
			xReturn = xQueueSend(Test_Queue,
							 &keycode,
							 0);					
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
        /*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
        if (DHT11_Read_TempAndHumidity(& DHT11_Data) == SUCCESS)
        {			
            printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n", \
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
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 		
		vTaskDelay(1000);
	}
}
static void LED_Task(void *arg)
{
	BaseType_t xReturn = pdTRUE;
	uint8_t r_queue;
	while(1)
	{		
		xReturn = xQueueReceive(Test_Queue,
								&r_queue,
								portMAX_DELAY);
		if(xReturn == pdTRUE)	
		{
			if(r_queue == KEY_1_DOWN)
			{
				StartFlag = 1;
				SetRGBColor(0x0000ff);				
			}
			if(r_queue == KEY_1_UP)
			{
				StartFlag = 0;
				SetRGBColor(0x000000);
			}
		}			
		else
			printf("���ݽ��ճ��� 0x%lx\r\n",xReturn);
	}
}
static void TIME_Task(void* arg)
{
	uint8_t RunFlag = 0;
	while(1)
	{
		if(!RunFlag)
		{
			if(time5s == 4999)
			{
				printf("time = 5s \r\n");
				RunFlag = 1;
			}			
		}
		else
		{
			if(time5s != 4999)
			{
				RunFlag = 0;
			}
		}
	}
}

