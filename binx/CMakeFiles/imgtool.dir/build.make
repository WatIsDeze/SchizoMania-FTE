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
CMAKE_SOURCE_DIR = /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin

# Include any dependencies generated for this target.
include CMakeFiles/imgtool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imgtool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imgtool.dir/flags.make

CMakeFiles/imgtool.dir/engine/client/image.c.o: CMakeFiles/imgtool.dir/flags.make
CMakeFiles/imgtool.dir/engine/client/image.c.o: engine/client/image.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/imgtool.dir/engine/client/image.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/imgtool.dir/engine/client/image.c.o   -c /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/engine/client/image.c

CMakeFiles/imgtool.dir/engine/client/image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgtool.dir/engine/client/image.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/engine/client/image.c > CMakeFiles/imgtool.dir/engine/client/image.c.i

CMakeFiles/imgtool.dir/engine/client/image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgtool.dir/engine/client/image.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/engine/client/image.c -o CMakeFiles/imgtool.dir/engine/client/image.c.s

CMakeFiles/imgtool.dir/imgtool.c.o: CMakeFiles/imgtool.dir/flags.make
CMakeFiles/imgtool.dir/imgtool.c.o: imgtool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/imgtool.dir/imgtool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/imgtool.dir/imgtool.c.o   -c /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/imgtool.c

CMakeFiles/imgtool.dir/imgtool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgtool.dir/imgtool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/imgtool.c > CMakeFiles/imgtool.dir/imgtool.c.i

CMakeFiles/imgtool.dir/imgtool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgtool.dir/imgtool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/imgtool.c -o CMakeFiles/imgtool.dir/imgtool.c.s

# Object files for target imgtool
imgtool_OBJECTS = \
"CMakeFiles/imgtool.dir/engine/client/image.c.o" \
"CMakeFiles/imgtool.dir/imgtool.c.o"

# External object files for target imgtool
imgtool_EXTERNAL_OBJECTS =

imgtool: CMakeFiles/imgtool.dir/engine/client/image.c.o
imgtool: CMakeFiles/imgtool.dir/imgtool.c.o
imgtool: CMakeFiles/imgtool.dir/build.make
imgtool: /usr/lib/x86_64-linux-gnu/libz.so
imgtool: /usr/lib/x86_64-linux-gnu/libjpeg.so
imgtool: /usr/lib/x86_64-linux-gnu/libpng.so
imgtool: /usr/lib/x86_64-linux-gnu/libz.so
imgtool: /usr/lib/x86_64-linux-gnu/libfreetype.so
imgtool: /usr/lib/x86_64-linux-gnu/libjpeg.so
imgtool: /usr/lib/x86_64-linux-gnu/libpng.so
imgtool: /usr/lib/x86_64-linux-gnu/libfreetype.so
imgtool: CMakeFiles/imgtool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable imgtool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgtool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imgtool.dir/build: imgtool

.PHONY : CMakeFiles/imgtool.dir/build

CMakeFiles/imgtool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imgtool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imgtool.dir/clean

CMakeFiles/imgtool.dir/depend:
	cd /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/CMakeFiles/imgtool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imgtool.dir/depend

