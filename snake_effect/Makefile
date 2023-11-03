#Copyrights mohanad

#for building snake_effect.elf and snake_effect.hex

snake.elf: main.o Lib/libmylib.a
	avr-gcc -mmcu=atmega32 -Wall main.o Lib/libmylib.a -lm -o snake.elf
	rm main.o
	avr-objcopy -O ihex snake.elf snake.hex
	mv snake.elf snake.hex build/
	touch build/binaryReport.txt
	echo  "This info about snake.elf" > build/binaryReport.txt
	avr-size build/snake.elf >> build/binaryReport.txt
	echo  "\n" >> build/binaryReport.txt
	echo  "This info about snake.hex" >> build/binaryReport.txt
	avr-size build/snake.hex >> build/binaryReport.txt
main.o: Src/main.c
	avr-gcc -mmcu=atmega32 -c -Wall Src/main.c -I Inc/ -I Lib/ -o main.o


