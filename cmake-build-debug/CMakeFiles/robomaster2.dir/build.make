# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\20887\CLionProjects\robomaster2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/robomaster2.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/robomaster2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robomaster2.dir/flags.make

CMakeFiles/robomaster2.dir/main.cpp.obj: CMakeFiles/robomaster2.dir/flags.make
CMakeFiles/robomaster2.dir/main.cpp.obj: CMakeFiles/robomaster2.dir/includes_CXX.rsp
CMakeFiles/robomaster2.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robomaster2.dir/main.cpp.obj"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\robomaster2.dir\main.cpp.obj -c C:\Users\20887\CLionProjects\robomaster2\main.cpp

CMakeFiles/robomaster2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robomaster2.dir/main.cpp.i"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20887\CLionProjects\robomaster2\main.cpp > CMakeFiles\robomaster2.dir\main.cpp.i

CMakeFiles/robomaster2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robomaster2.dir/main.cpp.s"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20887\CLionProjects\robomaster2\main.cpp -o CMakeFiles\robomaster2.dir\main.cpp.s

CMakeFiles/robomaster2.dir/Armor.cpp.obj: CMakeFiles/robomaster2.dir/flags.make
CMakeFiles/robomaster2.dir/Armor.cpp.obj: CMakeFiles/robomaster2.dir/includes_CXX.rsp
CMakeFiles/robomaster2.dir/Armor.cpp.obj: ../Armor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/robomaster2.dir/Armor.cpp.obj"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\robomaster2.dir\Armor.cpp.obj -c C:\Users\20887\CLionProjects\robomaster2\Armor.cpp

CMakeFiles/robomaster2.dir/Armor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robomaster2.dir/Armor.cpp.i"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20887\CLionProjects\robomaster2\Armor.cpp > CMakeFiles\robomaster2.dir\Armor.cpp.i

CMakeFiles/robomaster2.dir/Armor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robomaster2.dir/Armor.cpp.s"
	D:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20887\CLionProjects\robomaster2\Armor.cpp -o CMakeFiles\robomaster2.dir\Armor.cpp.s

# Object files for target robomaster2
robomaster2_OBJECTS = \
"CMakeFiles/robomaster2.dir/main.cpp.obj" \
"CMakeFiles/robomaster2.dir/Armor.cpp.obj"

# External object files for target robomaster2
robomaster2_EXTERNAL_OBJECTS =

robomaster2.exe: CMakeFiles/robomaster2.dir/main.cpp.obj
robomaster2.exe: CMakeFiles/robomaster2.dir/Armor.cpp.obj
robomaster2.exe: CMakeFiles/robomaster2.dir/build.make
robomaster2.exe: D:/Clion-openCV/opencv/mingw-build/install/x64/mingw/lib/libopencv_highgui411.dll.a
robomaster2.exe: D:/Clion-openCV/opencv/mingw-build/install/x64/mingw/lib/libopencv_videoio411.dll.a
robomaster2.exe: D:/Clion-openCV/opencv/mingw-build/install/x64/mingw/lib/libopencv_imgcodecs411.dll.a
robomaster2.exe: D:/Clion-openCV/opencv/mingw-build/install/x64/mingw/lib/libopencv_imgproc411.dll.a
robomaster2.exe: D:/Clion-openCV/opencv/mingw-build/install/x64/mingw/lib/libopencv_core411.dll.a
robomaster2.exe: CMakeFiles/robomaster2.dir/linklibs.rsp
robomaster2.exe: CMakeFiles/robomaster2.dir/objects1.rsp
robomaster2.exe: CMakeFiles/robomaster2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable robomaster2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\robomaster2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robomaster2.dir/build: robomaster2.exe
.PHONY : CMakeFiles/robomaster2.dir/build

CMakeFiles/robomaster2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\robomaster2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/robomaster2.dir/clean

CMakeFiles/robomaster2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\20887\CLionProjects\robomaster2 C:\Users\20887\CLionProjects\robomaster2 C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug C:\Users\20887\CLionProjects\robomaster2\cmake-build-debug\CMakeFiles\robomaster2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robomaster2.dir/depend

