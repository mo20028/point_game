################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD_program.c \
../DIO-progarm.c \
../EXTI_program.c \
../GIE_program.c \
../LCD_proram.c \
../PORT_program.c \
../main.c 

OBJS += \
./CLCD_program.o \
./DIO-progarm.o \
./EXTI_program.o \
./GIE_program.o \
./LCD_proram.o \
./PORT_program.o \
./main.o 

C_DEPS += \
./CLCD_program.d \
./DIO-progarm.d \
./EXTI_program.d \
./GIE_program.d \
./LCD_proram.d \
./PORT_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


