################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/%.o ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/%.su ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/%.cyclo: ../ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/%.c ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F410Rx -c -I../Core/Inc -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/SEGGER/SeggerFreeRTOS" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/RTT/Config" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/RTT/RTT" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/SEGGER/Config" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/SEGGER/SEGGER" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/SEGGER/SYSVIEW" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/FreeRTOS/config" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/FreeRTOS/include" -I"E:/Workspace_rtos/rtos_proj/01_freertos_proj/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-SEGGER-2f-SeggerFreeRTOS-2f-Config-2f-Cortex-2d-M

clean-ThirdParty-2f-SEGGER-2f-SeggerFreeRTOS-2f-Config-2f-Cortex-2d-M:
	-$(RM) ./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.d ./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.o ./ThirdParty/SEGGER/SeggerFreeRTOS/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-SeggerFreeRTOS-2f-Config-2f-Cortex-2d-M

