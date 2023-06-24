#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#define USE_GPIO 1
#if USE_GPIO
#include "stm32f10x.h"
#define USE_GPIOA  1
#define USE_GPIOB  1
#define USE_GPIOC  1
#define USE_GPIOD  1
#define USE_GPIOE  1
#define USE_GPIOF  1
#define USE_GPIOG  1

// 把“位带地址+位序号”转换成别名地址的宏
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2)) 
// 把一个地址转换成一个指针
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 

// 把位带别名区地址转换成指针
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))   

// GPIO ODR 和 IDR 寄存器地址映射 
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C   
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C   
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C   
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C   
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C   
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C      
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C      
  
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)  //0x40010808   
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)  //0x40010C08   
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)  //0x40011008   
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)  //0x40011408   
#define GPIOE_IDR_Addr    (GPIOE_BASE+8)  //0x40011808   
#define GPIOF_IDR_Addr    (GPIOF_BASE+8)  //0x40011A08   
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)  //0x40011E08 

// 单独操作 GPIO的某一个IO口，n(0,1,2...16),n表示具体是哪一个IO口
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出   
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入   
  
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出   
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入   
  
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出   
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入   
  
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出   
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入   
  
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出   
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入  
  
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出   
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入  
  
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出   
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入  
void GPIO_Config(void);
#endif  //USE_GPIO
#endif  //__BSP_GPIO_H
