cmake_minimum_required(VERSION 3.21)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CPU Cortex-M3)

set(CMAKE_C_FLAGS "--cpu=${CPU} --c99")
set(CMAKE_CXX_FLAGS "--cpu=${CPU}  --cpp11")
set(CMAKE_ASM_FLAGS "--cpu=${CPU}   -c")
set(ARMCC_FROMELF "D:/Keil_v5/ARM/ARMCC/bin/fromelf.exe")
project(FreeRTOS C CXX ASM)
add_compile_options(--thumb)

include_directories(
        BSP/adc
        BSP/color_led
        BSP/DEBUG
        BSP/delay
        BSP/dht11
        BSP/dwt_delay
        BSP/GPIO
        BSP/Key
        FreeRTOS/include
        FreeRTOS/port/RVDS/ARM_CM3
        Libraries/CMSIS
        Libraries/STM32F10x_StdPeriph_Driver/inc
        User
)

add_compile_definitions(USE_STDPERIPH_DRIVER STM32F10X_HD)
                        #设置宏定义
add_compile_options(-g -O0 -D__MICROLIB --apcs=interwork --split_sections)
                    #设置编译选项
add_link_options(--library_type=microlib --strict --scatter=${CMAKE_SOURCE_DIR}/Project/Objects/BH-F103.sct
                 #加载microlib和sct文件
                 --summary_stderr --info summarysizes,sizes,totals,unused,veneers
                 #设置map信息,summarysizes会同时在终端输出
                 --load_addr_map_info --xref --callgraph --symbols
                 #map文件生成在cmake-build-debug目录下，文件名为：工程名.map
                 )

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        BSP/adc/bsp_adc.c
        BSP/color_led/bsp_color_led.c
        BSP/DEBUG/bsp_debug.c
        BSP/delay/bsp_delay.c
        BSP/dht11/bsp_dht11.c
        BSP/dwt_delay/core_delay.c
        BSP/GPIO/bsp_gpio.c
        BSP/Key/bsp_key.c
        Libraries/CMSIS/startup/startup_stm32f10x_hd.s
        Libraries/CMSIS/core_cm3.c
        Libraries/CMSIS/system_stm32f10x.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
        Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
        Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
        User/main.c
        User/stm32f10x_it.c
        FreeRTOS/port/MemMang/heap_4.c
        FreeRTOS/port/RVDS/ARM_CM3/port.c
        FreeRTOS/src/croutine.c
        FreeRTOS/src/timers.c
        FreeRTOS/src/tasks.c
        FreeRTOS/src/queue.c
        FreeRTOS/src/list.c
        FreeRTOS/src/event_groups.c
        )

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${ARMCC_FROMELF} --text -z $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Print memory info")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${ARMCC_FROMELF} --output ${HEX_FILE} --i32 $<TARGET_FILE:${PROJECT_NAME}>
        COMMAND ${ARMCC_FROMELF} --output ${BIN_FILE} --bin $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Building ${HEX_FILE} and ${BIN_FILE}")
