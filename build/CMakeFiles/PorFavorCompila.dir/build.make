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
CMAKE_SOURCE_DIR = "/home/martu/Facu/Taller I/Taller-Worms"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/martu/Facu/Taller I/Taller-Worms/build"

# Include any dependencies generated for this target.
include CMakeFiles/PorFavorCompila.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PorFavorCompila.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PorFavorCompila.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PorFavorCompila.dir/flags.make

CMakeFiles/PorFavorCompila.dir/main.cpp.o: CMakeFiles/PorFavorCompila.dir/flags.make
CMakeFiles/PorFavorCompila.dir/main.cpp.o: ../main.cpp
CMakeFiles/PorFavorCompila.dir/main.cpp.o: CMakeFiles/PorFavorCompila.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PorFavorCompila.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PorFavorCompila.dir/main.cpp.o -MF CMakeFiles/PorFavorCompila.dir/main.cpp.o.d -o CMakeFiles/PorFavorCompila.dir/main.cpp.o -c "/home/martu/Facu/Taller I/Taller-Worms/main.cpp"

CMakeFiles/PorFavorCompila.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PorFavorCompila.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/main.cpp" > CMakeFiles/PorFavorCompila.dir/main.cpp.i

CMakeFiles/PorFavorCompila.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PorFavorCompila.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/main.cpp" -o CMakeFiles/PorFavorCompila.dir/main.cpp.s

CMakeFiles/PorFavorCompila.dir/screen.cpp.o: CMakeFiles/PorFavorCompila.dir/flags.make
CMakeFiles/PorFavorCompila.dir/screen.cpp.o: ../screen.cpp
CMakeFiles/PorFavorCompila.dir/screen.cpp.o: CMakeFiles/PorFavorCompila.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PorFavorCompila.dir/screen.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PorFavorCompila.dir/screen.cpp.o -MF CMakeFiles/PorFavorCompila.dir/screen.cpp.o.d -o CMakeFiles/PorFavorCompila.dir/screen.cpp.o -c "/home/martu/Facu/Taller I/Taller-Worms/screen.cpp"

CMakeFiles/PorFavorCompila.dir/screen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PorFavorCompila.dir/screen.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/screen.cpp" > CMakeFiles/PorFavorCompila.dir/screen.cpp.i

CMakeFiles/PorFavorCompila.dir/screen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PorFavorCompila.dir/screen.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/screen.cpp" -o CMakeFiles/PorFavorCompila.dir/screen.cpp.s

# Object files for target PorFavorCompila
PorFavorCompila_OBJECTS = \
"CMakeFiles/PorFavorCompila.dir/main.cpp.o" \
"CMakeFiles/PorFavorCompila.dir/screen.cpp.o"

# External object files for target PorFavorCompila
PorFavorCompila_EXTERNAL_OBJECTS =

PorFavorCompila: CMakeFiles/PorFavorCompila.dir/main.cpp.o
PorFavorCompila: CMakeFiles/PorFavorCompila.dir/screen.cpp.o
PorFavorCompila: CMakeFiles/PorFavorCompila.dir/build.make
PorFavorCompila: thirdParty/box2d/bin/libbox2d.a
PorFavorCompila: thirdParty/SDL2pp/libSDL2pp.so.8.3.0
PorFavorCompila: /usr/lib/x86_64-linux-gnu/libSDL2.so
PorFavorCompila: /usr/lib/x86_64-linux-gnu/libSDL2main.a
PorFavorCompila: /usr/local/lib/libSDL2_image.so
PorFavorCompila: /usr/local/lib/libSDL2_ttf.so
PorFavorCompila: /usr/local/lib/libSDL2_mixer.so
PorFavorCompila: CMakeFiles/PorFavorCompila.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PorFavorCompila"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PorFavorCompila.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PorFavorCompila.dir/build: PorFavorCompila
.PHONY : CMakeFiles/PorFavorCompila.dir/build

CMakeFiles/PorFavorCompila.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PorFavorCompila.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PorFavorCompila.dir/clean

CMakeFiles/PorFavorCompila.dir/depend:
	cd "/home/martu/Facu/Taller I/Taller-Worms/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/martu/Facu/Taller I/Taller-Worms" "/home/martu/Facu/Taller I/Taller-Worms" "/home/martu/Facu/Taller I/Taller-Worms/build" "/home/martu/Facu/Taller I/Taller-Worms/build" "/home/martu/Facu/Taller I/Taller-Worms/build/CMakeFiles/PorFavorCompila.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PorFavorCompila.dir/depend

