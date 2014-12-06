################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ADC_Temp.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/Cpu.c \
../Generated_Code/Delay_ms.c \
../Generated_Code/LED.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/UART.c \
../Generated_Code/Vdd_Sensor.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/ADC_Temp.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/Cpu.o \
./Generated_Code/Delay_ms.o \
./Generated_Code/LED.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/UART.o \
./Generated_Code/Vdd_Sensor.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/ADC_Temp.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/Cpu.d \
./Generated_Code/Delay_ms.d \
./Generated_Code/LED.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/UART.d \
./Generated_Code/Vdd_Sensor.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Freescale\KDS_1.1.1\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/David/workspace.kds/LPM_con_sensor_temperatura_v2/Sources" -I"C:/Users/David/workspace.kds/LPM_con_sensor_temperatura_v2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


