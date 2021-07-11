################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RF24/utility/ATXMegaD3/compatibility.c \
../src/RF24/utility/ATXMegaD3/gpio_helper.c 

CPP_SRCS += \
../src/RF24/utility/ATXMegaD3/gpio.cpp \
../src/RF24/utility/ATXMegaD3/spi.cpp 

OBJS += \
./src/RF24/utility/ATXMegaD3/compatibility.o \
./src/RF24/utility/ATXMegaD3/gpio.o \
./src/RF24/utility/ATXMegaD3/gpio_helper.o \
./src/RF24/utility/ATXMegaD3/spi.o 

C_DEPS += \
./src/RF24/utility/ATXMegaD3/compatibility.d \
./src/RF24/utility/ATXMegaD3/gpio_helper.d 

CPP_DEPS += \
./src/RF24/utility/ATXMegaD3/gpio.d \
./src/RF24/utility/ATXMegaD3/spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/RF24/utility/ATXMegaD3/%.o: ../src/RF24/utility/ATXMegaD3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/RF24/utility/ATXMegaD3/%.o: ../src/RF24/utility/ATXMegaD3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


