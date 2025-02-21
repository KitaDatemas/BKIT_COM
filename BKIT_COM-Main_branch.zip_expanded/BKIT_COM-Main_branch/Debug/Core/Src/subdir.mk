################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Application_Layer.c \
../Core/Src/global.c \
../Core/Src/main.c \
../Core/Src/pb_common.c \
../Core/Src/pb_decode.c \
../Core/Src/pb_encode.c \
../Core/Src/sensor_data.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/test.pb.c 

OBJS += \
./Core/Src/Application_Layer.o \
./Core/Src/global.o \
./Core/Src/main.o \
./Core/Src/pb_common.o \
./Core/Src/pb_decode.o \
./Core/Src/pb_encode.o \
./Core/Src/sensor_data.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/test.pb.o 

C_DEPS += \
./Core/Src/Application_Layer.d \
./Core/Src/global.d \
./Core/Src/main.d \
./Core/Src/pb_common.d \
./Core/Src/pb_decode.d \
./Core/Src/pb_encode.d \
./Core/Src/sensor_data.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/test.pb.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Application_Layer.cyclo ./Core/Src/Application_Layer.d ./Core/Src/Application_Layer.o ./Core/Src/Application_Layer.su ./Core/Src/global.cyclo ./Core/Src/global.d ./Core/Src/global.o ./Core/Src/global.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pb_common.cyclo ./Core/Src/pb_common.d ./Core/Src/pb_common.o ./Core/Src/pb_common.su ./Core/Src/pb_decode.cyclo ./Core/Src/pb_decode.d ./Core/Src/pb_decode.o ./Core/Src/pb_decode.su ./Core/Src/pb_encode.cyclo ./Core/Src/pb_encode.d ./Core/Src/pb_encode.o ./Core/Src/pb_encode.su ./Core/Src/sensor_data.cyclo ./Core/Src/sensor_data.d ./Core/Src/sensor_data.o ./Core/Src/sensor_data.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/test.pb.cyclo ./Core/Src/test.pb.d ./Core/Src/test.pb.o ./Core/Src/test.pb.su

.PHONY: clean-Core-2f-Src

