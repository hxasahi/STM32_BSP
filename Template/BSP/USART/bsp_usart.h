#ifndef __BSP_USART_H_
#define	__BSP_USART_H_
#define USE_USART  1
#if USE_USART
#include "stm32f10x.h"
#include <stdio.h>

#define USE_USART1  0
#define USE_USART2  0
#define USE_USART3  0
#define USE_UART4  0
#define USE_UART5  0	

#if USE_USART1
// 串口1-USART1

#define  USART1_BAUDRATE           115200
// USART GPIO 引脚宏定义
#define  USART1_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  USART1_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  USART1_TX_GPIO_PORT       GPIOA
#define  USART1_TX_GPIO_PIN        GPIO_Pin_9
#define  USART1_RX_GPIO_PORT       GPIOA
#define  USART1_RX_GPIO_PIN        GPIO_Pin_10

#endif //USE_USART1
#if USE_USART2
// 串口2-USART2
#define  USART2_BAUDRATE           115200
// USART GPIO 引脚宏定义
#define  USART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  USART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  USART2_TX_GPIO_PORT       GPIOA   
#define  USART2_TX_GPIO_PIN        GPIO_Pin_2
#define  USART2_RX_GPIO_PORT       GPIOA
#define  USART2_RX_GPIO_PIN        GPIO_Pin_3

#endif //USE_USART2

#if USE_USART3
// 串口3-USART3
#define  USART3_BAUDRATE           115200
// USART GPIO 引脚宏定义
#define  USART3_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  USART3_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  USART3_TX_GPIO_PORT       GPIOB   
#define  USART3_TX_GPIO_PIN        GPIO_Pin_10
#define  USART3_RX_GPIO_PORT       GPIOB
#define  USART3_RX_GPIO_PIN        GPIO_Pin_11
#endif //USE_USART3

#if USE_UART4
// 串口4-UART4
#define  UART4_BAUDRATE           115200
// USART GPIO 引脚宏定义
#define  UART4_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  UART4_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  UART4_TX_GPIO_PORT       GPIOC   
#define  UART4_TX_GPIO_PIN        GPIO_Pin_10
#define  UART4_RX_GPIO_PORT       GPIOC
#define  UART4_RX_GPIO_PIN        GPIO_Pin_11
#endif //USE_UART4

#if USE_UART5
// 串口5-UART5
#define  UART5_BAUDRATE           115200
// USART GPIO 引脚宏定义
#define  UART5_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  UART5_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  UART5_TX_GPIO_PORT       GPIOC   
#define  UART5_TX_GPIO_PIN        GPIO_Pin_12
#define  UART5_RX_GPIO_PORT       GPIOD
#define  UART5_RX_GPIO_PIN        GPIO_Pin_2
#endif //USE_UART5

void USART_Config(void);
void USART_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void USART_SendString( USART_TypeDef * pUSARTx, char *str);
void USART_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
#endif //USE_USART
#endif /* __BSP_USART_H_ */
