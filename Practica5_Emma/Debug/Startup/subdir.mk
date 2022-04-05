################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f429xx.s 

OBJS += \
./Startup/startup_stm32f429xx.o 

S_DEPS += \
./Startup/startup_stm32f429xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/CMSIS/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/Core/Inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/Practica5_Emma/Drivers/API" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f429xx.d ./Startup/startup_stm32f429xx.o

.PHONY: clean-Startup

