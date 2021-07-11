################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/check.cpp \
../src/main.cpp \
../src/receiver.cpp \
../src/scanner.cpp \
../src/transmitter.cpp 

OBJS += \
./src/check.o \
./src/main.o \
./src/receiver.o \
./src/scanner.o \
./src/transmitter.o 

CPP_DEPS += \
./src/check.d \
./src/main.d \
./src/receiver.d \
./src/scanner.d \
./src/transmitter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


