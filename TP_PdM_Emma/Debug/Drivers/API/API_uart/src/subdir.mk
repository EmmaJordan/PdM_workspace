################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/API_uart/src/API_uart.c 

OBJS += \
./Drivers/API/API_uart/src/API_uart.o 

C_DEPS += \
./Drivers/API/API_uart/src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/API_uart/src/%.o Drivers/API/API_uart/src/%.su: ../Drivers/API/API_uart/src/%.c Drivers/API/API_uart/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/CMSIS/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/API/API_uart/inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-API_uart-2f-src

clean-Drivers-2f-API-2f-API_uart-2f-src:
	-$(RM) ./Drivers/API/API_uart/src/API_uart.d ./Drivers/API/API_uart/src/API_uart.o ./Drivers/API/API_uart/src/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-API_uart-2f-src

