################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/driver/i2c.c \
../src/hw/driver/imu.c \
../src/hw/driver/kalman.c \
../src/hw/driver/led.c \
../src/hw/driver/madgwick_mahony.c \
../src/hw/driver/tim.c \
../src/hw/driver/uart.c 

OBJS += \
./src/hw/driver/i2c.o \
./src/hw/driver/imu.o \
./src/hw/driver/kalman.o \
./src/hw/driver/led.o \
./src/hw/driver/madgwick_mahony.o \
./src/hw/driver/tim.o \
./src/hw/driver/uart.o 

C_DEPS += \
./src/hw/driver/i2c.d \
./src/hw/driver/imu.d \
./src/hw/driver/kalman.d \
./src/hw/driver/led.d \
./src/hw/driver/madgwick_mahony.d \
./src/hw/driver/tim.d \
./src/hw/driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/driver/i2c.o: ../src/hw/driver/i2c.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/imu.o: ../src/hw/driver/imu.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/imu.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/kalman.o: ../src/hw/driver/kalman.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/kalman.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/led.o: ../src/hw/driver/led.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/led.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/madgwick_mahony.o: ../src/hw/driver/madgwick_mahony.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/madgwick_mahony.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/tim.o: ../src/hw/driver/tim.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hw/driver/uart.o: ../src/hw/driver/uart.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -c -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/ap" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/bsp" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/hw" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/CMSIS/Include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/lib/cube_imu/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/hw/include" -I"C:/STM32 Coding files/stm32f1_imu/exam_imu/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw/driver/uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

