# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/145/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/145/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/elio/CLionProjects/C-Course-Design

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elio/CLionProjects/C-Course-Design/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CDesign.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CDesign.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CDesign.dir/flags.make

CMakeFiles/CDesign.dir/test_main.c.o: CMakeFiles/CDesign.dir/flags.make
CMakeFiles/CDesign.dir/test_main.c.o: ../test_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elio/CLionProjects/C-Course-Design/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CDesign.dir/test_main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CDesign.dir/test_main.c.o   -c /home/elio/CLionProjects/C-Course-Design/test_main.c

CMakeFiles/CDesign.dir/test_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CDesign.dir/test_main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/elio/CLionProjects/C-Course-Design/test_main.c > CMakeFiles/CDesign.dir/test_main.c.i

CMakeFiles/CDesign.dir/test_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CDesign.dir/test_main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/elio/CLionProjects/C-Course-Design/test_main.c -o CMakeFiles/CDesign.dir/test_main.c.s

# Object files for target CDesign
CDesign_OBJECTS = \
"CMakeFiles/CDesign.dir/test_main.c.o"

# External object files for target CDesign
CDesign_EXTERNAL_OBJECTS =

../bin/CDesign: CMakeFiles/CDesign.dir/test_main.c.o
../bin/CDesign: CMakeFiles/CDesign.dir/build.make
../bin/CDesign: CMakeFiles/CDesign.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elio/CLionProjects/C-Course-Design/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/CDesign"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CDesign.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CDesign.dir/build: ../bin/CDesign

.PHONY : CMakeFiles/CDesign.dir/build

CMakeFiles/CDesign.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CDesign.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CDesign.dir/clean

CMakeFiles/CDesign.dir/depend:
	cd /home/elio/CLionProjects/C-Course-Design/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elio/CLionProjects/C-Course-Design /home/elio/CLionProjects/C-Course-Design /home/elio/CLionProjects/C-Course-Design/cmake-build-debug /home/elio/CLionProjects/C-Course-Design/cmake-build-debug /home/elio/CLionProjects/C-Course-Design/cmake-build-debug/CMakeFiles/CDesign.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CDesign.dir/depend

