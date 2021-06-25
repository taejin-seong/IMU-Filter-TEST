################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/hw.c 

OBJS += \
./src/hw/hw.o 

C_DEPS += \
./src/hw/hw.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/hw.o: ../src/hw/hw.c src/hw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/hw.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

