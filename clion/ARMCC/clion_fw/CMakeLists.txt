cmake_minimum_required(VERSION 3.21)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CPU Cortex-M3)

set(CMAKE_C_FLAGS "--cpu=${CPU}  --c99")
set(CMAKE_CXX_FLAGS "--cpu=${CPU} --cpp11")
set(CMAKE_ASM_FLAGS "--cpu=${CPU} -c")
set(ARMCC_FROMELF "D:/Keil_v5/ARM/ARMCC/bin/fromelf.exe")
project(clion_fw C CXX ASM)

add_compile_options(--thumb)

include_directories(
        BSP/DEBUG
        BSP/delay
        BSP/GPIO
        BSP/Key
        BSP/Systick
        BSP/USART
        Libraries/CMSIS
        Libraries/STM32F10x_StdPeriph_Driver/inc
        User
)

add_compile_definitions(USE_STDPERIPH_DRIVER STM32F10X_HD)

add_link_options(--branchpatch=sdcomp-29491-629360 --strict --summary_stderr --info sizes,totals,unused,veneers --load_addr_map_info --xref --callgraph --symbols)
add_link_options(--library_type=microlib --scatter=${CMAKE_SOURCE_DIR}/Project/Objects/BH-F103.sct)
add_compile_options(-O0 -D__MICROLIB --apcs=interwork --split_sections)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        BSP/DEBUG/bsp_debug.c
        BSP/delay/bsp_delay.c
        BSP/GPIO/bsp_gpio.c
        BSP/Key/bsp_key.c
        BSP/Systick/bsp_SysTick.c
        BSP/USART/bsp_usart.c
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
