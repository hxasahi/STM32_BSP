#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "arm_math.h"
#include "arm_nnfunctions.h"

#define data_len 5
int main(void)
{ 
    int i;
    q7_t data_in[data_len]={-100,-2,0,2,100};    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
    
    for(i=0;i<data_len;i++)
    {
        printf("%d,",data_in[i]);
    }
    printf("\r\n");
    arm_relu_q7(data_in,data_len);
    for(i=0;i<data_len;i++)
    {
        printf("%d,",data_in[i]);
    }
    printf("\r\n");
}

