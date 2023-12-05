cmake_minimum_required(VERSION 3.22.1)

project(snake_effect2)

set(CMAKE_C_COMPILER "avr-gcc")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=atmega32")

set(SOURCES Src/main.c)

set(LIB_SOURCES Lib/DIO_programe.c)

add_library(DIO_programe STATIC ${LIB_SOURCES})

target_include_directories(DIO_programe PUBLIC Lib/ Inc/)

add_executable(snake ${SOURCES})

target_link_libraries(snake DIO_programe)

target_include_directories(snake PRIVATE Inc/ Lib/ Src/ )

set_target_properties(snake PROPERTIES OUTPUT_NAME snake.elf)

add_custom_target(generate_hex
    COMMAND avr-objcopy -O ihex snake.elf snake.hex && avr-size snake.elf > binaryReport.txt
    DEPENDS snake
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)