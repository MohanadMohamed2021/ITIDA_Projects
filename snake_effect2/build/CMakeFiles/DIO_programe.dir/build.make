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
include CMakeFiles/DIO_programe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DIO_programe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DIO_programe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DIO_programe.dir/flags.make

CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o: CMakeFiles/DIO_programe.dir/flags.make
CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o: ../Lib/DIO_programe.c
CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o: CMakeFiles/DIO_programe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mohanad/Documents/test/snake_effect2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o -MF CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o.d -o CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o -c /home/mohanad/Documents/test/snake_effect2/Lib/DIO_programe.c

CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.i"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mohanad/Documents/test/snake_effect2/Lib/DIO_programe.c > CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.i

CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.s"
	avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mohanad/Documents/test/snake_effect2/Lib/DIO_programe.c -o CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.s

# Object files for target DIO_programe
DIO_programe_OBJECTS = \
"CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o"

# External object files for target DIO_programe
DIO_programe_EXTERNAL_OBJECTS =

libDIO_programe.a: CMakeFiles/DIO_programe.dir/Lib/DIO_programe.c.o
libDIO_programe.a: CMakeFiles/DIO_programe.dir/build.make
libDIO_programe.a: CMakeFiles/DIO_programe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mohanad/Documents/test/snake_effect2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libDIO_programe.a"
	$(CMAKE_COMMAND) -P CMakeFiles/DIO_programe.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DIO_programe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DIO_programe.dir/build: libDIO_programe.a
.PHONY : CMakeFiles/DIO_programe.dir/build

CMakeFiles/DIO_programe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DIO_programe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DIO_programe.dir/clean

CMakeFiles/DIO_programe.dir/depend:
	cd /home/mohanad/Documents/test/snake_effect2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build/CMakeFiles/DIO_programe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DIO_programe.dir/depend

