#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_debug.h"
#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_dht11.h"
#include "core_delay.h"

static void AppTaskCreate(void *arg);
static void Key_Task(void *parameter);
static void Test_Task(void *parameter);
static TaskHandle_t AppTaskCreateHandle = NULL;
static TaskHandle_t Key_Task_Handle = NULL;
static TaskHandle_t Test_Task_Handle = NULL;
int main(void)
{
    BaseType_t xReturn = pdPASS;
    DEBUG_Config();
#if USE_KEY
    KEY_Init();    
#endif  //USE_KEY   
    DHT11_Init();
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
        vTaskDelay(20);
#endif  //USE_KEY       
    }
}
static void Test_Task(void *parameter)
{
    DHT11_Data_TypeDef DHT11_Data;
    while (1)
    {
        printf("1\r\n");
        CPU_TS_Tmr_Delay_US(1000);
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
        vTaskDelay(2000);
    }
}
