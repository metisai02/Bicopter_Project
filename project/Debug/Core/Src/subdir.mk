################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GUI.c \
../Core/Src/crc.c \
../Core/Src/drone_controller.c \
../Core/Src/frame_uart.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/mpu9255.c \
../Core/Src/nrf24.c \
../Core/Src/pid.c \
../Core/Src/radio_demo.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/GUI.o \
./Core/Src/crc.o \
./Core/Src/drone_controller.o \
./Core/Src/frame_uart.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/mpu9255.o \
./Core/Src/nrf24.o \
./Core/Src/pid.o \
./Core/Src/radio_demo.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/GUI.d \
./Core/Src/crc.d \
./Core/Src/drone_controller.d \
./Core/Src/frame_uart.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/mpu9255.d \
./Core/Src/nrf24.d \
./Core/Src/pid.d \
./Core/Src/radio_demo.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GUI.cyclo ./Core/Src/GUI.d ./Core/Src/GUI.o ./Core/Src/GUI.su ./Core/Src/crc.cyclo ./Core/Src/crc.d ./Core/Src/crc.o ./Core/Src/crc.su ./Core/Src/drone_controller.cyclo ./Core/Src/drone_controller.d ./Core/Src/drone_controller.o ./Core/Src/drone_controller.su ./Core/Src/frame_uart.cyclo ./Core/Src/frame_uart.d ./Core/Src/frame_uart.o ./Core/Src/frame_uart.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/mpu9255.cyclo ./Core/Src/mpu9255.d ./Core/Src/mpu9255.o ./Core/Src/mpu9255.su ./Core/Src/nrf24.cyclo ./Core/Src/nrf24.d ./Core/Src/nrf24.o ./Core/Src/nrf24.su ./Core/Src/pid.cyclo ./Core/Src/pid.d ./Core/Src/pid.o ./Core/Src/pid.su ./Core/Src/radio_demo.cyclo ./Core/Src/radio_demo.d ./Core/Src/radio_demo.o ./Core/Src/radio_demo.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

