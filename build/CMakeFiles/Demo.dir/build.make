# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/dobot_cr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/dobot_cr/build

# Include any dependencies generated for this target.
include CMakeFiles/Demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Demo.dir/flags.make

CMakeFiles/Demo.dir/src/Demo.o: CMakeFiles/Demo.dir/flags.make
CMakeFiles/Demo.dir/src/Demo.o: ../src/Demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/dobot_cr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Demo.dir/src/Demo.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Demo.dir/src/Demo.o -c /home/pi/dobot_cr/src/Demo.cpp

CMakeFiles/Demo.dir/src/Demo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Demo.dir/src/Demo.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/dobot_cr/src/Demo.cpp > CMakeFiles/Demo.dir/src/Demo.i

CMakeFiles/Demo.dir/src/Demo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Demo.dir/src/Demo.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/dobot_cr/src/Demo.cpp -o CMakeFiles/Demo.dir/src/Demo.s

CMakeFiles/Demo.dir/src/RealTimeData.o: CMakeFiles/Demo.dir/flags.make
CMakeFiles/Demo.dir/src/RealTimeData.o: ../src/RealTimeData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/dobot_cr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Demo.dir/src/RealTimeData.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Demo.dir/src/RealTimeData.o -c /home/pi/dobot_cr/src/RealTimeData.cpp

CMakeFiles/Demo.dir/src/RealTimeData.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Demo.dir/src/RealTimeData.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/dobot_cr/src/RealTimeData.cpp > CMakeFiles/Demo.dir/src/RealTimeData.i

CMakeFiles/Demo.dir/src/RealTimeData.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Demo.dir/src/RealTimeData.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/dobot_cr/src/RealTimeData.cpp -o CMakeFiles/Demo.dir/src/RealTimeData.s

CMakeFiles/Demo.dir/src/SocketUtils.o: CMakeFiles/Demo.dir/flags.make
CMakeFiles/Demo.dir/src/SocketUtils.o: ../src/SocketUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/dobot_cr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Demo.dir/src/SocketUtils.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Demo.dir/src/SocketUtils.o -c /home/pi/dobot_cr/src/SocketUtils.cpp

CMakeFiles/Demo.dir/src/SocketUtils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Demo.dir/src/SocketUtils.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/dobot_cr/src/SocketUtils.cpp > CMakeFiles/Demo.dir/src/SocketUtils.i

CMakeFiles/Demo.dir/src/SocketUtils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Demo.dir/src/SocketUtils.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/dobot_cr/src/SocketUtils.cpp -o CMakeFiles/Demo.dir/src/SocketUtils.s

# Object files for target Demo
Demo_OBJECTS = \
"CMakeFiles/Demo.dir/src/Demo.o" \
"CMakeFiles/Demo.dir/src/RealTimeData.o" \
"CMakeFiles/Demo.dir/src/SocketUtils.o"

# External object files for target Demo
Demo_EXTERNAL_OBJECTS =

Demo: CMakeFiles/Demo.dir/src/Demo.o
Demo: CMakeFiles/Demo.dir/src/RealTimeData.o
Demo: CMakeFiles/Demo.dir/src/SocketUtils.o
Demo: CMakeFiles/Demo.dir/build.make
Demo: CMakeFiles/Demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/dobot_cr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Demo.dir/build: Demo

.PHONY : CMakeFiles/Demo.dir/build

CMakeFiles/Demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Demo.dir/clean

CMakeFiles/Demo.dir/depend:
	cd /home/pi/dobot_cr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dobot_cr /home/pi/dobot_cr /home/pi/dobot_cr/build /home/pi/dobot_cr/build /home/pi/dobot_cr/build/CMakeFiles/Demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Demo.dir/depend

