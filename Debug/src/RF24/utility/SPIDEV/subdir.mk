################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RF24/utility/SPIDEV/compatibility.c \
../src/RF24/utility/SPIDEV/interrupt.c 

CPP_SRCS += \
../src/RF24/utility/SPIDEV/gpio.cpp \
../src/RF24/utility/SPIDEV/spi.cpp 

OBJS += \
./src/RF24/utility/SPIDEV/compatibility.o \
./src/RF24/utility/SPIDEV/gpio.o \
./src/RF24/utility/SPIDEV/interrupt.o \
./src/RF24/utility/SPIDEV/spi.o 

C_DEPS += \
./src/RF24/utility/SPIDEV/compatibility.d \
./src/RF24/utility/SPIDEV/interrupt.d 

CPP_DEPS += \
./src/RF24/utility/SPIDEV/gpio.d \
./src/RF24/utility/SPIDEV/spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/RF24/utility/SPIDEV/%.o: ../src/RF24/utility/SPIDEV/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/RF24/utility/SPIDEV/%.o: ../src/RF24/utility/SPIDEV/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


