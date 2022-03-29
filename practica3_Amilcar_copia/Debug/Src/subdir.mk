################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main_Amilcar.c 

OBJS += \
./Src/main_Amilcar.o 

C_DEPS += \
./Src/main_Amilcar.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/practica3_Amilcar_copia/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/practica3_Amilcar_copia/Drivers/CMSIS/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/practica3_Amilcar_copia/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/practica3_Amilcar_copia/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Win10/Desktop/RepoPdM_Jordan/PdM_workspace/practica3_Amilcar_copia/Drivers/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main_Amilcar.d ./Src/main_Amilcar.o ./Src/main_Amilcar.su

.PHONY: clean-Src

