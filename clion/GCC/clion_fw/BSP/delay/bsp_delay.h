#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H
#define USE_DELAY  1
#if USE_DELAY
#include "stm32f10x.h"

void Delay_10us(__IO u32 nTime);
#define Delay_ms(x) Delay_10us(100*x)	 //µ¥Î»ms

void TimingDelay_Decrement(void);
#endif  //USE_DELAY
#endif /* __BSP_DELAY_H */
