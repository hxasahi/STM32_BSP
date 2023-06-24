#include "bsp_delay.h"
#if USE_DELAY
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told,tnow,reload,tcnt=0;

    reload = SysTick->LOAD;                     //获取重装载寄存器值
    ticks = nus * (SystemCoreClock / 1000000);  //计数时间值   括号里的代表1us秒嘀嗒定时器的value会向下降多少值
    told=SysTick->VAL;                          //获取当前数值寄存器值（开始时数值）

    while(1)
    {
          tnow=SysTick->VAL;          //获取当前数值寄存器值
          if(tnow!=told)              //当前值不等于开始值说明已在计数
          {         

                 if(tnow<told)             //当前值小于开始数值，说明未计到0
                      tcnt+=told-tnow;     //计数值=开始值-当前值

                 else                  //当前值大于开始数值，说明已计到0并重新计数
                        tcnt+=reload-tnow+told;   //计数值=重装载值-当前值+开始值  （已
                                                  //从开始值计到0） 
                 told=tnow;                //更新开始值
                 if(tcnt>=ticks)break;     //时间超过/等于要延迟的时间,则退出.
          } 
    }     
}

#endif  //USE_DELAY
