#Copyrights mohanad

#for building snake_effect.elf and snake_effect.hex

#*********Manage Varibles*******

Target_name = snake.elf
Flag1 = -c -Wall
Flag2 = -Wall 
CC=avr-gcc -mmcu=atmega32
APP_Object_file_Path = main.o
APP_Source_file_Path = Src/main.c
Path_of_lib_headers = Inc/ 
Path_of_DIO_headers = Lib/
Static_Library_Path = Lib/libmylib.a 
Convert_To_Hex = avr-objcopy -O ihex
Name_of_Hex = snake.hex
Path_Of_Report = build/binaryReport.txt 
Get_info = avr-size



#*********Generating Build Files*********

$(Target_name): $(APP_Object_file_Path)  $(Static_Library_Path)
	$(CC) $^ -lm -o $@
	rm $(APP_Object_file_Path)
	$(Convert_To_Hex) $@ $(Name_of_Hex)
	mv $@ $(Name_of_Hex) build/
	touch $(Path_Of_Report)
	echo  "This info about snake.elf" > $(Path_Of_Report)
	$(Get_info) build/$@ >> $(Path_Of_Report)
	echo  "\n" >> $(Path_Of_Report)
	echo  "This info about snake.hex" >> $(Path_Of_Report)
	$(Get_info) build/$(Name_of_Hex) >> $(Path_Of_Report)

$(APP_Object_file_Path): $(APP_Source_file_Path)
	$(CC) $(Flag1) $< -I $(Path_of_lib_headers) -I $(Path_of_DIO_headers) -o $@


