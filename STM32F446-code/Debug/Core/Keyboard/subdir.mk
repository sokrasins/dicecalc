################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Keyboard/Keyboard.cpp 

OBJS += \
./Core/Keyboard/Keyboard.o 

CPP_DEPS += \
./Core/Keyboard/Keyboard.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Keyboard/Keyboard.o: ../Core/Keyboard/Keyboard.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Symbol -I../Core/Eval -I../Core/Keyboard -I../Core/Display -I../Core/Device -I../Core/RNG -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Keyboard/Keyboard.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

