################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main_PdM.c 

OBJS += \
./Src/main_PdM.o 

C_DEPS += \
./Src/main_PdM.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/CMSIS/Include" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/API/inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/Core/Inc" -I"C:/Users/Win10/Desktop/Repositorios CESE/RepoPdM_Jordan/PdM_workspace/TP_PdM_Emma/Drivers/API" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main_PdM.d ./Src/main_PdM.o ./Src/main_PdM.su

.PHONY: clean-Src

