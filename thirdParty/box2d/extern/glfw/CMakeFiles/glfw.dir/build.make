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
CMAKE_BINARY_DIR = "/home/martu/Facu/Taller I/Taller-Worms"

# Include any dependencies generated for this target.
include thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.make

# Include the progress variables for this target.
include thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/progress.make

# Include the compile flags for this target's objects.
include thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o: thirdParty/box2d/extern/glfw/src/context.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o -MF CMakeFiles/glfw.dir/src/context.c.o.d -o CMakeFiles/glfw.dir/src/context.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/context.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/context.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/context.c" > CMakeFiles/glfw.dir/src/context.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/context.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/context.c" -o CMakeFiles/glfw.dir/src/context.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o: thirdParty/box2d/extern/glfw/src/init.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o -MF CMakeFiles/glfw.dir/src/init.c.o.d -o CMakeFiles/glfw.dir/src/init.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/init.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/init.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/init.c" > CMakeFiles/glfw.dir/src/init.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/init.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/init.c" -o CMakeFiles/glfw.dir/src/init.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o: thirdParty/box2d/extern/glfw/src/input.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o -MF CMakeFiles/glfw.dir/src/input.c.o.d -o CMakeFiles/glfw.dir/src/input.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/input.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/input.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/input.c" > CMakeFiles/glfw.dir/src/input.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/input.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/input.c" -o CMakeFiles/glfw.dir/src/input.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o: thirdParty/box2d/extern/glfw/src/monitor.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o -MF CMakeFiles/glfw.dir/src/monitor.c.o.d -o CMakeFiles/glfw.dir/src/monitor.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/monitor.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/monitor.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/monitor.c" > CMakeFiles/glfw.dir/src/monitor.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/monitor.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/monitor.c" -o CMakeFiles/glfw.dir/src/monitor.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o: thirdParty/box2d/extern/glfw/src/vulkan.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o -MF CMakeFiles/glfw.dir/src/vulkan.c.o.d -o CMakeFiles/glfw.dir/src/vulkan.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/vulkan.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/vulkan.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/vulkan.c" > CMakeFiles/glfw.dir/src/vulkan.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/vulkan.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/vulkan.c" -o CMakeFiles/glfw.dir/src/vulkan.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o: thirdParty/box2d/extern/glfw/src/window.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o -MF CMakeFiles/glfw.dir/src/window.c.o.d -o CMakeFiles/glfw.dir/src/window.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/window.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/window.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/window.c" > CMakeFiles/glfw.dir/src/window.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/window.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/window.c" -o CMakeFiles/glfw.dir/src/window.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o: thirdParty/box2d/extern/glfw/src/x11_init.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o -MF CMakeFiles/glfw.dir/src/x11_init.c.o.d -o CMakeFiles/glfw.dir/src/x11_init.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_init.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/x11_init.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_init.c" > CMakeFiles/glfw.dir/src/x11_init.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/x11_init.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_init.c" -o CMakeFiles/glfw.dir/src/x11_init.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o: thirdParty/box2d/extern/glfw/src/x11_monitor.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o -MF CMakeFiles/glfw.dir/src/x11_monitor.c.o.d -o CMakeFiles/glfw.dir/src/x11_monitor.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_monitor.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/x11_monitor.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_monitor.c" > CMakeFiles/glfw.dir/src/x11_monitor.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/x11_monitor.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_monitor.c" -o CMakeFiles/glfw.dir/src/x11_monitor.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o: thirdParty/box2d/extern/glfw/src/x11_window.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o -MF CMakeFiles/glfw.dir/src/x11_window.c.o.d -o CMakeFiles/glfw.dir/src/x11_window.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_window.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/x11_window.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_window.c" > CMakeFiles/glfw.dir/src/x11_window.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/x11_window.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/x11_window.c" -o CMakeFiles/glfw.dir/src/x11_window.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o: thirdParty/box2d/extern/glfw/src/xkb_unicode.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o -MF CMakeFiles/glfw.dir/src/xkb_unicode.c.o.d -o CMakeFiles/glfw.dir/src/xkb_unicode.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/xkb_unicode.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/xkb_unicode.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/xkb_unicode.c" > CMakeFiles/glfw.dir/src/xkb_unicode.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/xkb_unicode.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/xkb_unicode.c" -o CMakeFiles/glfw.dir/src/xkb_unicode.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o: thirdParty/box2d/extern/glfw/src/posix_time.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o -MF CMakeFiles/glfw.dir/src/posix_time.c.o.d -o CMakeFiles/glfw.dir/src/posix_time.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_time.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/posix_time.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_time.c" > CMakeFiles/glfw.dir/src/posix_time.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/posix_time.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_time.c" -o CMakeFiles/glfw.dir/src/posix_time.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o: thirdParty/box2d/extern/glfw/src/posix_thread.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o -MF CMakeFiles/glfw.dir/src/posix_thread.c.o.d -o CMakeFiles/glfw.dir/src/posix_thread.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_thread.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/posix_thread.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_thread.c" > CMakeFiles/glfw.dir/src/posix_thread.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/posix_thread.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/posix_thread.c" -o CMakeFiles/glfw.dir/src/posix_thread.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o: thirdParty/box2d/extern/glfw/src/glx_context.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o -MF CMakeFiles/glfw.dir/src/glx_context.c.o.d -o CMakeFiles/glfw.dir/src/glx_context.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/glx_context.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/glx_context.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/glx_context.c" > CMakeFiles/glfw.dir/src/glx_context.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/glx_context.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/glx_context.c" -o CMakeFiles/glfw.dir/src/glx_context.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o: thirdParty/box2d/extern/glfw/src/egl_context.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o -MF CMakeFiles/glfw.dir/src/egl_context.c.o.d -o CMakeFiles/glfw.dir/src/egl_context.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/egl_context.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/egl_context.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/egl_context.c" > CMakeFiles/glfw.dir/src/egl_context.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/egl_context.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/egl_context.c" -o CMakeFiles/glfw.dir/src/egl_context.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o: thirdParty/box2d/extern/glfw/src/osmesa_context.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o -MF CMakeFiles/glfw.dir/src/osmesa_context.c.o.d -o CMakeFiles/glfw.dir/src/osmesa_context.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/osmesa_context.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/osmesa_context.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/osmesa_context.c" > CMakeFiles/glfw.dir/src/osmesa_context.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/osmesa_context.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/osmesa_context.c" -o CMakeFiles/glfw.dir/src/osmesa_context.c.s

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/flags.make
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o: thirdParty/box2d/extern/glfw/src/linux_joystick.c
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Building C object thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o -MF CMakeFiles/glfw.dir/src/linux_joystick.c.o.d -o CMakeFiles/glfw.dir/src/linux_joystick.c.o -c "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/linux_joystick.c"

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/src/linux_joystick.c.i"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/linux_joystick.c" > CMakeFiles/glfw.dir/src/linux_joystick.c.i

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/src/linux_joystick.c.s"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/src/linux_joystick.c" -o CMakeFiles/glfw.dir/src/linux_joystick.c.s

# Object files for target glfw
glfw_OBJECTS = \
"CMakeFiles/glfw.dir/src/context.c.o" \
"CMakeFiles/glfw.dir/src/init.c.o" \
"CMakeFiles/glfw.dir/src/input.c.o" \
"CMakeFiles/glfw.dir/src/monitor.c.o" \
"CMakeFiles/glfw.dir/src/vulkan.c.o" \
"CMakeFiles/glfw.dir/src/window.c.o" \
"CMakeFiles/glfw.dir/src/x11_init.c.o" \
"CMakeFiles/glfw.dir/src/x11_monitor.c.o" \
"CMakeFiles/glfw.dir/src/x11_window.c.o" \
"CMakeFiles/glfw.dir/src/xkb_unicode.c.o" \
"CMakeFiles/glfw.dir/src/posix_time.c.o" \
"CMakeFiles/glfw.dir/src/posix_thread.c.o" \
"CMakeFiles/glfw.dir/src/glx_context.c.o" \
"CMakeFiles/glfw.dir/src/egl_context.c.o" \
"CMakeFiles/glfw.dir/src/osmesa_context.c.o" \
"CMakeFiles/glfw.dir/src/linux_joystick.c.o"

# External object files for target glfw
glfw_EXTERNAL_OBJECTS =

thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/context.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/init.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/input.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/monitor.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/vulkan.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/window.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_init.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_monitor.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/x11_window.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/xkb_unicode.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_time.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/posix_thread.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/glx_context.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/egl_context.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/osmesa_context.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/src/linux_joystick.c.o
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/build.make
thirdParty/box2d/bin/libglfw.a: thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/martu/Facu/Taller I/Taller-Worms/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_17) "Linking C static library ../../bin/libglfw.a"
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean_target.cmake
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glfw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/build: thirdParty/box2d/bin/libglfw.a
.PHONY : thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/build

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/clean:
	cd "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean.cmake
.PHONY : thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/clean

thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/depend:
	cd "/home/martu/Facu/Taller I/Taller-Worms" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/martu/Facu/Taller I/Taller-Worms" "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" "/home/martu/Facu/Taller I/Taller-Worms" "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw" "/home/martu/Facu/Taller I/Taller-Worms/thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : thirdParty/box2d/extern/glfw/CMakeFiles/glfw.dir/depend

