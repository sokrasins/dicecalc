################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/RNG/Aes.c \
../Core/RNG/SHA256.c 

CPP_SRCS += \
../Core/RNG/Entropy.cpp \
../Core/RNG/Prng.cpp 

C_DEPS += \
./Core/RNG/Aes.d \
./Core/RNG/SHA256.d 

OBJS += \
./Core/RNG/Aes.o \
./Core/RNG/Entropy.o \
./Core/RNG/Prng.o \
./Core/RNG/SHA256.o 

CPP_DEPS += \
./Core/RNG/Entropy.d \
./Core/RNG/Prng.d 


# Each subdirectory must supply rules for building sources it contributes
Core/RNG/Aes.o: ../Core/RNG/Aes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Symbol -I../Core/Eval -I../Core/Keyboard -I../Core/Display -I../Core/Device -I../Core/RNG -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/RNG/Aes.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/RNG/Entropy.o: ../Core/RNG/Entropy.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Symbol -I../Core/Eval -I../Core/Keyboard -I../Core/Display -I../Core/Device -I../Core/RNG -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/RNG/Entropy.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/RNG/Prng.o: ../Core/RNG/Prng.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Symbol -I../Core/Eval -I../Core/Keyboard -I../Core/Display -I../Core/Device -I../Core/RNG -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/RNG/Prng.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/RNG/SHA256.o: ../Core/RNG/SHA256.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Symbol -I../Core/Eval -I../Core/Keyboard -I../Core/Display -I../Core/Device -I../Core/RNG -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/RNG/SHA256.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

