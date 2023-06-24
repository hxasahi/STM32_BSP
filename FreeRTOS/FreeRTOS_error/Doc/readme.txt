Systick中断频率由
port.c文件中
vPortSetupTimerInterrupt函数
configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ参数确定

configSYSTICK_CLOCK_HZ = configCPU_CLOCK_HZ
configTICK_RATE_HZ
在FreeRTOSConfig.h里设置为100_000(10us中断一次)

然后在
stm32f10x_it.c文件中
systick中断里面
计数到1ms后调用FreeRTOS的中断服务函数xPortSysTickHandler
