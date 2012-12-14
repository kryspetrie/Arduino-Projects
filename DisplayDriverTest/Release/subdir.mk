################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Buffer.cpp \
../Buffer2D.cpp \
../ChildBuffer2D.cpp \
../DisplayDriverTest.cpp \
../Font.cpp \
../LedDisplay.cpp \
../SimpleFont.cpp 

OBJS += \
./Buffer.o \
./Buffer2D.o \
./ChildBuffer2D.o \
./DisplayDriverTest.o \
./Font.o \
./LedDisplay.o \
./SimpleFont.o 

CPP_DEPS += \
./Buffer.d \
./Buffer2D.d \
./ChildBuffer2D.d \
./DisplayDriverTest.d \
./Font.d \
./LedDisplay.d \
./SimpleFont.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\dev\arduino\ide\hardware\arduino\cores\arduino" -I"C:\dev\arduino\ide\hardware\arduino\variants\standard" -I"C:\Users\cpetrie\git\Arduino\DisplayDriverTest" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=102 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega168 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


