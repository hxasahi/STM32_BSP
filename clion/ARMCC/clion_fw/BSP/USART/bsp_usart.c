#include "bsp_usart.h"
#if USE_USART && (USE_USART1||USE_USART2||USE_USART3||USE_USART4||USE_USART5)
/**
 * @brief  配置嵌套向量中断控制器NVIC
 * @param  无
 * @retval 无
 */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* 配置USART为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    /* 抢断优先级*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* 子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* 初始化配置NVIC */
    NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;	
}

/**
 * @brief  USART GPIO 配置,工作参数配置
 * @param  无
 * @retval 无
 */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	
#if USE_USART1	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
	// 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = USART1_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

    //将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = USART1_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
    USART_InitStructure.USART_BaudRate = USART1_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    NVIC_Configuration();
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
#endif //USE_USART1

#if USE_USART2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	
	// 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = USART2_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

    //将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = USART2_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	// 配置串口的工作参数
    USART_InitStructure.USART_BaudRate = USART2_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    NVIC_Configuration();
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
#endif //USE_USART2

#if USE_USART3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	// 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = USART3_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

    //将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = USART3_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	// 配置串口的工作参数
    USART_InitStructure.USART_BaudRate = USART3_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    NVIC_Configuration();
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);
#endif //USE_USART3

#if USE_UART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	// 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = UART4_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART4_TX_GPIO_PORT, &GPIO_InitStructure);

    //将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = UART4_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART4_RX_GPIO_PORT, &GPIO_InitStructure);
	// 配置串口的工作参数
    USART_InitStructure.USART_BaudRate = UART4_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);
    NVIC_Configuration();
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART4, ENABLE);
#endif //USE_UART4

#if USE_UART5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	// 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = UART5_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART5_TX_GPIO_PORT, &GPIO_InitStructure);

    //将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = UART5_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART5_RX_GPIO_PORT, &GPIO_InitStructure);
	// 配置串口的工作参数
    USART_InitStructure.USART_BaudRate = UART5_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART5, &USART_InitStructure);
    NVIC_Configuration();
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);
#endif //USE_UART5
}

/*****************  发送一个字节 **********************/
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);

    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/****************** 发送8位的数组 ************************/
void USART_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num)
{
    uint8_t i;

    for (i = 0; i < num; i++)
    {
        /* 发送一个字节数据到USART */
        USART_SendByte(pUSARTx, array[i]);

    }
    /* 等待发送完成 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/*****************  发送字符串 **********************/
void USART_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        USART_SendByte(pUSARTx, *(str + k));
        k++;
    }
    while (*(str + k) != '\0');

    /* 等待发送完成 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {}
}

/*****************  发送一个16位数 **********************/
void USART_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch)
{
    uint8_t temp_h, temp_l;

    /* 取出高八位 */
    temp_h = (ch & 0XFF00) >> 8;
    /* 取出低八位 */
    temp_l = ch & 0XFF;

    /* 发送高八位 */
    USART_SendData(pUSARTx, temp_h);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

    /* 发送低八位 */
    USART_SendData(pUSARTx, temp_l);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

#endif //USE_USART
