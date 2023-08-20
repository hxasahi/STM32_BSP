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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
    
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

