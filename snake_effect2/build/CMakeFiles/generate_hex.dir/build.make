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

# Utility rule file for generate_hex.

# Include any custom commands dependencies for this target.
include CMakeFiles/generate_hex.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/generate_hex.dir/progress.make

CMakeFiles/generate_hex: snake.elf
	avr-objcopy -O ihex snake.elf snake.hex && avr-size snake.elf > binaryReport.txt

generate_hex: CMakeFiles/generate_hex
generate_hex: CMakeFiles/generate_hex.dir/build.make
.PHONY : generate_hex

# Rule to build all files generated by this target.
CMakeFiles/generate_hex.dir/build: generate_hex
.PHONY : CMakeFiles/generate_hex.dir/build

CMakeFiles/generate_hex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generate_hex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generate_hex.dir/clean

CMakeFiles/generate_hex.dir/depend:
	cd /home/mohanad/Documents/test/snake_effect2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2 /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build /home/mohanad/Documents/test/snake_effect2/build/CMakeFiles/generate_hex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/generate_hex.dir/depend

