# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/atifany/Desktop/CppGraphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/atifany/Desktop/CppGraphics/build

# Include any dependencies generated for this target.
include CMakeFiles/cpp_graphics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_graphics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_graphics.dir/flags.make

CMakeFiles/cpp_graphics.dir/sources/main.cpp.o: CMakeFiles/cpp_graphics.dir/flags.make
CMakeFiles/cpp_graphics.dir/sources/main.cpp.o: ../sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/atifany/Desktop/CppGraphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_graphics.dir/sources/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_graphics.dir/sources/main.cpp.o -c /home/atifany/Desktop/CppGraphics/sources/main.cpp

CMakeFiles/cpp_graphics.dir/sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_graphics.dir/sources/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/atifany/Desktop/CppGraphics/sources/main.cpp > CMakeFiles/cpp_graphics.dir/sources/main.cpp.i

CMakeFiles/cpp_graphics.dir/sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_graphics.dir/sources/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/atifany/Desktop/CppGraphics/sources/main.cpp -o CMakeFiles/cpp_graphics.dir/sources/main.cpp.s

CMakeFiles/cpp_graphics.dir/sources/glad.c.o: CMakeFiles/cpp_graphics.dir/flags.make
CMakeFiles/cpp_graphics.dir/sources/glad.c.o: ../sources/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/atifany/Desktop/CppGraphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cpp_graphics.dir/sources/glad.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cpp_graphics.dir/sources/glad.c.o   -c /home/atifany/Desktop/CppGraphics/sources/glad.c

CMakeFiles/cpp_graphics.dir/sources/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cpp_graphics.dir/sources/glad.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/atifany/Desktop/CppGraphics/sources/glad.c > CMakeFiles/cpp_graphics.dir/sources/glad.c.i

CMakeFiles/cpp_graphics.dir/sources/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cpp_graphics.dir/sources/glad.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/atifany/Desktop/CppGraphics/sources/glad.c -o CMakeFiles/cpp_graphics.dir/sources/glad.c.s

CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o: CMakeFiles/cpp_graphics.dir/flags.make
CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o: ../sources/process_input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/atifany/Desktop/CppGraphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o -c /home/atifany/Desktop/CppGraphics/sources/process_input.cpp

CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/atifany/Desktop/CppGraphics/sources/process_input.cpp > CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.i

CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/atifany/Desktop/CppGraphics/sources/process_input.cpp -o CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.s

CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o: CMakeFiles/cpp_graphics.dir/flags.make
CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o: ../sources/core_data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/atifany/Desktop/CppGraphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o -c /home/atifany/Desktop/CppGraphics/sources/core_data.cpp

CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/atifany/Desktop/CppGraphics/sources/core_data.cpp > CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.i

CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/atifany/Desktop/CppGraphics/sources/core_data.cpp -o CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.s

# Object files for target cpp_graphics
cpp_graphics_OBJECTS = \
"CMakeFiles/cpp_graphics.dir/sources/main.cpp.o" \
"CMakeFiles/cpp_graphics.dir/sources/glad.c.o" \
"CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o" \
"CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o"

# External object files for target cpp_graphics
cpp_graphics_EXTERNAL_OBJECTS =

cpp_graphics: CMakeFiles/cpp_graphics.dir/sources/main.cpp.o
cpp_graphics: CMakeFiles/cpp_graphics.dir/sources/glad.c.o
cpp_graphics: CMakeFiles/cpp_graphics.dir/sources/process_input.cpp.o
cpp_graphics: CMakeFiles/cpp_graphics.dir/sources/core_data.cpp.o
cpp_graphics: CMakeFiles/cpp_graphics.dir/build.make
cpp_graphics: CMakeFiles/cpp_graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/atifany/Desktop/CppGraphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cpp_graphics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp_graphics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_graphics.dir/build: cpp_graphics

.PHONY : CMakeFiles/cpp_graphics.dir/build

CMakeFiles/cpp_graphics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp_graphics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp_graphics.dir/clean

CMakeFiles/cpp_graphics.dir/depend:
	cd /home/atifany/Desktop/CppGraphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/atifany/Desktop/CppGraphics /home/atifany/Desktop/CppGraphics /home/atifany/Desktop/CppGraphics/build /home/atifany/Desktop/CppGraphics/build /home/atifany/Desktop/CppGraphics/build/CMakeFiles/cpp_graphics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp_graphics.dir/depend

