# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mohanad/Documents/test/snake_effect2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mohanad/Documents/test/snake_effect2/build

# Include any dependencies generated for this target.
include CMakeFiles/snake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/snake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snake.dir/flags.make

CMakeFiles/snake.dir/Src/main.c.o: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/Src/main.c.o: ../Src/main.c
CMakeFiles/snake.dir/Src/main.c.o: CMakeFiles/snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mohanad/Documents/test/snake_effect2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/snake.dir/Src/main.c.o"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/snake.dir/Src/main.c.o -MF CMakeFiles/snake.dir/Src/main.c.o.d -o CMakeFiles/snake.dir/Src/main.c.o -c /home/mohanad/Documents/test/snake_effect2/Src/main.c

CMakeFiles/snake.dir/Src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/Src/main.c.i"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mohanad/Documents/test/snake_effect2/Src/main.c > CMakeFiles/snake.dir/Src/main.c.i

CMakeFiles/snake.dir/Src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/Src/main.c.s"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mohanad/Documents/test/snake_effect2/Src/main.c -o CMakeFiles/snake.dir/Src/main.c.s

# Object files for target snake
snake_OBJECTS = \
"CMakeFiles/snake.dir/Src/main.c.o"

# External object files for target snake
snake_EXTERNAL_OBJECTS =

snake.elf: CMakeFiles/snake.dir/Src/main.c.o
snake.elf: CMakeFiles/snake.dir/build.make
snake.elf: libDIO_programe.a
snake.elf: CMakeFiles/snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mohanad/Documents/test/snake_effect2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable snake.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/snake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/snake.dir/build: snake.elf
.PHONY : CMakeFiles/snake.dir/build

CMakeFiles/snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/snake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/snake.dir/clean

CMakeFiles/snake.dir/depend:
	cd /home/mohanad/Documents/test/snake_effect2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build/CMakeFiles/snake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/snake.dir/depend

