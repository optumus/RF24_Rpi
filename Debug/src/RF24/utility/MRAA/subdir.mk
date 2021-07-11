################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RF24/utility/MRAA/compatibility.c 

CPP_SRCS += \
../src/RF24/utility/MRAA/gpio.cpp \
../src/RF24/utility/MRAA/spi.cpp 

OBJS += \
./src/RF24/utility/MRAA/compatibility.o \
./src/RF24/utility/MRAA/gpio.o \
./src/RF24/utility/MRAA/spi.o 

C_DEPS += \
./src/RF24/utility/MRAA/compatibility.d 

CPP_DEPS += \
./src/RF24/utility/MRAA/gpio.d \
./src/RF24/utility/MRAA/spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/RF24/utility/MRAA/%.o: ../src/RF24/utility/MRAA/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/RF24/utility/MRAA/%.o: ../src/RF24/utility/MRAA/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


