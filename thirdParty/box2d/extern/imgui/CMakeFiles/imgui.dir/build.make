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
CMAKE_SOURCE_DIR = /home/joaco/cuatri/taller/tp3_worms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joaco/cuatri/taller/tp3_worms

# Include any dependencies generated for this target.
include thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/depend.make

# Include the progress variables for this target.
include thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/flags.make

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.o: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/flags.make
thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.o: thirdParty/box2d/extern/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaco/cuatri/taller/tp3_worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.o"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui.cpp.o -c /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui.cpp

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui.cpp.i"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui.cpp.i

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui.cpp.s"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui.cpp.s

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.o: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/flags.make
thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.o: thirdParty/box2d/extern/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaco/cuatri/taller/tp3_worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.o"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui_demo.cpp.o -c /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_demo.cpp

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_demo.cpp.i"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/imgui_demo.cpp.i

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_demo.cpp.s"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/imgui_demo.cpp.s

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/flags.make
thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o: thirdParty/box2d/extern/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaco/cuatri/taller/tp3_worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui_draw.cpp.o -c /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_draw.cpp

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_draw.cpp.i"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui_draw.cpp.i

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_draw.cpp.s"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui_draw.cpp.s

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/flags.make
thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o: thirdParty/box2d/extern/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaco/cuatri/taller/tp3_worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui_widgets.cpp.o -c /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_widgets.cpp

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_widgets.cpp.i"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/imgui_widgets.cpp.i

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_widgets.cpp.s"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/imgui_widgets.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui_widgets.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui.cpp.o
thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.o
thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o
thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o
thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/build.make
thirdParty/box2d/bin/libimgui.a: thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joaco/cuatri/taller/tp3_worms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../../bin/libimgui.a"
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/build: thirdParty/box2d/bin/libimgui.a

.PHONY : thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/build

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/clean:
	cd /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/clean

thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/depend:
	cd /home/joaco/cuatri/taller/tp3_worms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joaco/cuatri/taller/tp3_worms /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui /home/joaco/cuatri/taller/tp3_worms /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui /home/joaco/cuatri/taller/tp3_worms/thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdParty/box2d/extern/imgui/CMakeFiles/imgui.dir/depend

