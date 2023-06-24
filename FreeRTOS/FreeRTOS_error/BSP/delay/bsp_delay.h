#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H
#define USE_DELAY  1
#if USE_DELAY
#include "stm32f10x.h"
void delay_us(u32 nus);
#endif  //USE_DELAY
#endif /* __BSP_DELAY_H */
