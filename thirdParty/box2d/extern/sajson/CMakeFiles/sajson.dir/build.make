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
CMAKE_SOURCE_DIR = /home/monke/Desktop/Taller/Taller-Worms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/monke/Desktop/Taller/Taller-Worms

# Include any dependencies generated for this target.
include thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/compiler_depend.make

# Include the progress variables for this target.
include thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/progress.make

# Include the compile flags for this target's objects.
include thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/flags.make

thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o: thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/flags.make
thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o: thirdParty/box2d/extern/sajson/sajson.cpp
thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o: thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/monke/Desktop/Taller/Taller-Worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o"
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o -MF CMakeFiles/sajson.dir/sajson.cpp.o.d -o CMakeFiles/sajson.dir/sajson.cpp.o -c /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson/sajson.cpp

thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sajson.dir/sajson.cpp.i"
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson/sajson.cpp > CMakeFiles/sajson.dir/sajson.cpp.i

thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sajson.dir/sajson.cpp.s"
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson/sajson.cpp -o CMakeFiles/sajson.dir/sajson.cpp.s

# Object files for target sajson
sajson_OBJECTS = \
"CMakeFiles/sajson.dir/sajson.cpp.o"

# External object files for target sajson
sajson_EXTERNAL_OBJECTS =

thirdParty/box2d/bin/libsajson.a: thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o
thirdParty/box2d/bin/libsajson.a: thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/build.make
thirdParty/box2d/bin/libsajson.a: thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/monke/Desktop/Taller/Taller-Worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../bin/libsajson.a"
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && $(CMAKE_COMMAND) -P CMakeFiles/sajson.dir/cmake_clean_target.cmake
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sajson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/build: thirdParty/box2d/bin/libsajson.a
.PHONY : thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/build

thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/clean:
	cd /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson && $(CMAKE_COMMAND) -P CMakeFiles/sajson.dir/cmake_clean.cmake
.PHONY : thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/clean

thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/depend:
	cd /home/monke/Desktop/Taller/Taller-Worms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/monke/Desktop/Taller/Taller-Worms /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson /home/monke/Desktop/Taller/Taller-Worms /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson /home/monke/Desktop/Taller/Taller-Worms/thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdParty/box2d/extern/sajson/CMakeFiles/sajson.dir/depend

