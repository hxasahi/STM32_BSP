#include "bsp_delay.h"
#if USE_DELAY
static __IO u32 TimingDelay;

/**
  * @brief   us��ʱ����,10usΪһ����λ
  * @param  
  *		@arg nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
  * @retval  ��
  */
void Delay_10us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  ��ȡ���ĳ���
  * @param  ��
  * @retval ��
  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
  */
//10usִ��һ��
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
#endif  //USE_DELAY
