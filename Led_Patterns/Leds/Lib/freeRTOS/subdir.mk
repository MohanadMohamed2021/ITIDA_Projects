################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../KPD_program.c \
../PDF1_LAB1.c \
../croutine.c \
../heap_1.c \
../lcd_programme.c \
../list.c \
../port.c \
../programme\ file.c \
../queue.c \
../tasks.c \
../timers.c 

OBJS += \
./KPD_program.o \
./PDF1_LAB1.o \
./croutine.o \
./heap_1.o \
./lcd_programme.o \
./list.o \
./port.o \
./programme\ file.o \
./queue.o \
./tasks.o \
./timers.o 

C_DEPS += \
./KPD_program.d \
./PDF1_LAB1.d \
./croutine.d \
./heap_1.d \
./lcd_programme.d \
./list.d \
./port.d \
./programme\ file.d \
./queue.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

programme\ file.o: ../programme\ file.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"programme file.d" -MT"programme\ file.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


