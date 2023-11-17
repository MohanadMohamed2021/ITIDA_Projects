# FreeRTOS Makefile

# Compiler and flags
CC = avr-gcc
CFLAGS = -mmcu=atmega32 -I ../../Inc -I ./

# Source files
SRC_DIR = ./
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIR)))

# Object files
OBJ = $(SRC:.c=.o)

# Target: libFreeRTOS.a
libFreeRTOS.a: $(OBJ)
	ar rcs libFreeRTOS.a $^
	rm -f *.o

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files
clean:
	rm -f libFreeRTOS.a *.o