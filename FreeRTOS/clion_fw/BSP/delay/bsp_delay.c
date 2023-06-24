#include "bsp_delay.h"
#if USE_DELAY
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told,tnow,reload,tcnt=0;

    reload = SysTick->LOAD;                     //��ȡ��װ�ؼĴ���ֵ
    ticks = nus * (SystemCoreClock / 1000000);  //����ʱ��ֵ   ������Ĵ���1us����શ�ʱ����value�����½�����ֵ
    told=SysTick->VAL;                          //��ȡ��ǰ��ֵ�Ĵ���ֵ����ʼʱ��ֵ��

    while(1)
    {
          tnow=SysTick->VAL;          //��ȡ��ǰ��ֵ�Ĵ���ֵ
          if(tnow!=told)              //��ǰֵ�����ڿ�ʼֵ˵�����ڼ���
          {         

                 if(tnow<told)             //��ǰֵС�ڿ�ʼ��ֵ��˵��δ�Ƶ�0
                      tcnt+=told-tnow;     //����ֵ=��ʼֵ-��ǰֵ

                 else                  //��ǰֵ���ڿ�ʼ��ֵ��˵���ѼƵ�0�����¼���
                        tcnt+=reload-tnow+told;   //����ֵ=��װ��ֵ-��ǰֵ+��ʼֵ  ����
                                                  //�ӿ�ʼֵ�Ƶ�0�� 
                 told=tnow;                //���¿�ʼֵ
                 if(tcnt>=ticks)break;     //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
          } 
    }     
}

#endif  //USE_DELAY
