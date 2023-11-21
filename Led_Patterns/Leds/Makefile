# Copyrights mohanad

# Compiler and flags
CC = avr-gcc
CFLAGS = -mmcu=atmega32 -I Src/ -I Inc/ -I Lib/ -I Lib/freeRTOS/ -I Lib/KPD/ -I Lib/DIO/ -I Lib/LCD/ -I Lib/TIMER

# Source files
SRC_DIR = Src Lib freeRTOS
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIR)))

# Object files
OBJ = $(SRC:.c=.o)

# Library files
LIBS = Lib/libModule.a Lib/libFreeRTOS.a

# Target: led.elf
led.elf: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $^ -o led.elf
	mv led.elf build/
	avr-size build/led.elf > build/BinaryReport.txt

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

