# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/in_order.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/in_order.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/in_order.dir/flags.make

CMakeFiles/in_order.dir/main.cpp.o: CMakeFiles/in_order.dir/flags.make
CMakeFiles/in_order.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/in_order.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/in_order.dir/main.cpp.o -c "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/main.cpp"

CMakeFiles/in_order.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/in_order.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/main.cpp" > CMakeFiles/in_order.dir/main.cpp.i

CMakeFiles/in_order.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/in_order.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/main.cpp" -o CMakeFiles/in_order.dir/main.cpp.s

CMakeFiles/in_order.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/in_order.dir/main.cpp.o.requires

CMakeFiles/in_order.dir/main.cpp.o.provides: CMakeFiles/in_order.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/in_order.dir/build.make CMakeFiles/in_order.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/in_order.dir/main.cpp.o.provides

CMakeFiles/in_order.dir/main.cpp.o.provides.build: CMakeFiles/in_order.dir/main.cpp.o


# Object files for target in_order
in_order_OBJECTS = \
"CMakeFiles/in_order.dir/main.cpp.o"

# External object files for target in_order
in_order_EXTERNAL_OBJECTS =

in_order: CMakeFiles/in_order.dir/main.cpp.o
in_order: CMakeFiles/in_order.dir/build.make
in_order: CMakeFiles/in_order.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable in_order"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/in_order.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/in_order.dir/build: in_order

.PHONY : CMakeFiles/in_order.dir/build

CMakeFiles/in_order.dir/requires: CMakeFiles/in_order.dir/main.cpp.o.requires

.PHONY : CMakeFiles/in_order.dir/requires

CMakeFiles/in_order.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/in_order.dir/cmake_clean.cmake
.PHONY : CMakeFiles/in_order.dir/clean

CMakeFiles/in_order.dir/depend:
	cd "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order" "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order" "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug" "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug" "/Users/nadezda/Desktop/ТП/алгоритмы/модуль 2/in-order/cmake-build-debug/CMakeFiles/in_order.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/in_order.dir/depend
