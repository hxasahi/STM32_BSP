#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#include "stm32f10x.h"

void Delay_us(__IO u32 nTime);
#define Delay_ms(x) Delay_us(100*x)	 //µ¥Î»ms

void TimingDelay_Decrement(void);

#endif /* __BSP_DELAY_H */
