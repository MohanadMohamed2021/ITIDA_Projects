#Copyrights mohanad
#create static library for (DIO_programe.c)

libmylib.a: DIO_programe.o
	ar rcs libmylib.a DIO_programe.o

DIO_programe.o: DIO_programe.c
	avr-gcc -mmcu=atmega32 -c DIO_programe.c -I ../Inc -o DIO_programe.o

clean_all:
	rm DIO_programe.o