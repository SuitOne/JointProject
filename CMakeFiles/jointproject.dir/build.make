# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/devooty/programming/JointProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/devooty/programming/JointProject

# Include any dependencies generated for this target.
include CMakeFiles/jointproject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jointproject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jointproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jointproject.dir/flags.make

CMakeFiles/jointproject.dir/src/main.cpp.o: CMakeFiles/jointproject.dir/flags.make
CMakeFiles/jointproject.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/jointproject.dir/src/main.cpp.o: CMakeFiles/jointproject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/devooty/programming/JointProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jointproject.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jointproject.dir/src/main.cpp.o -MF CMakeFiles/jointproject.dir/src/main.cpp.o.d -o CMakeFiles/jointproject.dir/src/main.cpp.o -c /home/devooty/programming/JointProject/src/main.cpp

CMakeFiles/jointproject.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jointproject.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/devooty/programming/JointProject/src/main.cpp > CMakeFiles/jointproject.dir/src/main.cpp.i

CMakeFiles/jointproject.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jointproject.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/devooty/programming/JointProject/src/main.cpp -o CMakeFiles/jointproject.dir/src/main.cpp.s

CMakeFiles/jointproject.dir/src/ChatClient.cpp.o: CMakeFiles/jointproject.dir/flags.make
CMakeFiles/jointproject.dir/src/ChatClient.cpp.o: src/ChatClient.cpp
CMakeFiles/jointproject.dir/src/ChatClient.cpp.o: CMakeFiles/jointproject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/devooty/programming/JointProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jointproject.dir/src/ChatClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jointproject.dir/src/ChatClient.cpp.o -MF CMakeFiles/jointproject.dir/src/ChatClient.cpp.o.d -o CMakeFiles/jointproject.dir/src/ChatClient.cpp.o -c /home/devooty/programming/JointProject/src/ChatClient.cpp

CMakeFiles/jointproject.dir/src/ChatClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jointproject.dir/src/ChatClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/devooty/programming/JointProject/src/ChatClient.cpp > CMakeFiles/jointproject.dir/src/ChatClient.cpp.i

CMakeFiles/jointproject.dir/src/ChatClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jointproject.dir/src/ChatClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/devooty/programming/JointProject/src/ChatClient.cpp -o CMakeFiles/jointproject.dir/src/ChatClient.cpp.s

CMakeFiles/jointproject.dir/src/ChatServer.cpp.o: CMakeFiles/jointproject.dir/flags.make
CMakeFiles/jointproject.dir/src/ChatServer.cpp.o: src/ChatServer.cpp
CMakeFiles/jointproject.dir/src/ChatServer.cpp.o: CMakeFiles/jointproject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/devooty/programming/JointProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jointproject.dir/src/ChatServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jointproject.dir/src/ChatServer.cpp.o -MF CMakeFiles/jointproject.dir/src/ChatServer.cpp.o.d -o CMakeFiles/jointproject.dir/src/ChatServer.cpp.o -c /home/devooty/programming/JointProject/src/ChatServer.cpp

CMakeFiles/jointproject.dir/src/ChatServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jointproject.dir/src/ChatServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/devooty/programming/JointProject/src/ChatServer.cpp > CMakeFiles/jointproject.dir/src/ChatServer.cpp.i

CMakeFiles/jointproject.dir/src/ChatServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jointproject.dir/src/ChatServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/devooty/programming/JointProject/src/ChatServer.cpp -o CMakeFiles/jointproject.dir/src/ChatServer.cpp.s

# Object files for target jointproject
jointproject_OBJECTS = \
"CMakeFiles/jointproject.dir/src/main.cpp.o" \
"CMakeFiles/jointproject.dir/src/ChatClient.cpp.o" \
"CMakeFiles/jointproject.dir/src/ChatServer.cpp.o"

# External object files for target jointproject
jointproject_EXTERNAL_OBJECTS =

jointproject: CMakeFiles/jointproject.dir/src/main.cpp.o
jointproject: CMakeFiles/jointproject.dir/src/ChatClient.cpp.o
jointproject: CMakeFiles/jointproject.dir/src/ChatServer.cpp.o
jointproject: CMakeFiles/jointproject.dir/build.make
jointproject: CMakeFiles/jointproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/devooty/programming/JointProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable jointproject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jointproject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jointproject.dir/build: jointproject
.PHONY : CMakeFiles/jointproject.dir/build

CMakeFiles/jointproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jointproject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jointproject.dir/clean

CMakeFiles/jointproject.dir/depend:
	cd /home/devooty/programming/JointProject && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/devooty/programming/JointProject /home/devooty/programming/JointProject /home/devooty/programming/JointProject /home/devooty/programming/JointProject /home/devooty/programming/JointProject/CMakeFiles/jointproject.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/jointproject.dir/depend

