################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/%.o Drivers/CMSIS/%.su: ../Drivers/CMSIS/%.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/CMSIS/Include" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/API/inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/Core/Inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/API" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32f4xx.d ./Drivers/CMSIS/system_stm32f4xx.o ./Drivers/CMSIS/system_stm32f4xx.su

.PHONY: clean-Drivers-2f-CMSIS

