################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RF24/RF24.cpp 

O_SRCS += \
../src/RF24/RF24.o \
../src/RF24/bcm2835.o \
../src/RF24/interrupt.o \
../src/RF24/spi.o 

OBJS += \
./src/RF24/RF24.o 

CPP_DEPS += \
./src/RF24/RF24.d 


# Each subdirectory must supply rules for building sources it contributes
src/RF24/%.o: ../src/RF24/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


