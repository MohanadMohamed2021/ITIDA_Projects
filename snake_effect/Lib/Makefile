#Copyrights mohanad
#create static library for (DIO_programe.c)
Flag = -c
CC=avr-gcc -mmcu=atmega32
Path_to_object_file = DIO_programe.o
Path_to_source_file = DIO_programe.c
Target_name = libmylib.a
Create_static_library = ar rcs
$(Target_name): $(Path_to_object_file)
	$(Create_static_library) $(Target_name) $(Path_to_object_file)
	rm $(Path_to_object_file)
$(Path_to_object_file): $(Path_to_source_file)
	$(CC) $(Flag) $< -I ../Inc -o $@
