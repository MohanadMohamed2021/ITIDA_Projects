# Copyrights mohanad
# Create a static library for all modules

# Compiler and flags
CC = avr-gcc
CFLAGS = -mmcu=atmega32 -I DIO/ -I ../Inc/ -I LCD/ -I KPD/ -I TIMER/

# Source files
SRC = DIO/dio_programe.c LCD/lcd_programme.c KPD/KPD_program.c TIMER/timer_programme.c

# Object files
OBJ = $(SRC:.c=.o)

# Target: libModule.a
libModule.a: $(OBJ)
	ar rcs libModule.a $^
	rm -f *.o

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove the static library and object files
clean:
	rm -f libModule.a *.o