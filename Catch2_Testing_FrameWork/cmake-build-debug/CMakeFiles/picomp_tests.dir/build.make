# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\testing_with_catch - Kopie - Kopie"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\testing_with_catch - Kopie - Kopie\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\picomp_tests.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\picomp_tests.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\picomp_tests.dir\flags.make

CMakeFiles\picomp_tests.dir\catch_main.cpp.obj: CMakeFiles\picomp_tests.dir\flags.make
CMakeFiles\picomp_tests.dir\catch_main.cpp.obj: ..\catch_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\testing_with_catch - Kopie - Kopie\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/picomp_tests.dir/catch_main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\picomp_tests.dir\catch_main.cpp.obj /FdCMakeFiles\picomp_tests.dir\ /FS -c "D:\testing_with_catch - Kopie - Kopie\catch_main.cpp"
<<

CMakeFiles\picomp_tests.dir\catch_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picomp_tests.dir/catch_main.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\picomp_tests.dir\catch_main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\testing_with_catch - Kopie - Kopie\catch_main.cpp"
<<

CMakeFiles\picomp_tests.dir\catch_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picomp_tests.dir/catch_main.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\picomp_tests.dir\catch_main.cpp.s /c "D:\testing_with_catch - Kopie - Kopie\catch_main.cpp"
<<

CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.obj: CMakeFiles\picomp_tests.dir\flags.make
CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.obj: ..\catch_tests_picomp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\testing_with_catch - Kopie - Kopie\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/picomp_tests.dir/catch_tests_picomp.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.obj /FdCMakeFiles\picomp_tests.dir\ /FS -c "D:\testing_with_catch - Kopie - Kopie\catch_tests_picomp.cpp"
<<

CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picomp_tests.dir/catch_tests_picomp.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\testing_with_catch - Kopie - Kopie\catch_tests_picomp.cpp"
<<

CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picomp_tests.dir/catch_tests_picomp.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.s /c "D:\testing_with_catch - Kopie - Kopie\catch_tests_picomp.cpp"
<<

# Object files for target picomp_tests
picomp_tests_OBJECTS = \
"CMakeFiles\picomp_tests.dir\catch_main.cpp.obj" \
"CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.obj"

# External object files for target picomp_tests
picomp_tests_EXTERNAL_OBJECTS =

picomp_tests.exe: CMakeFiles\picomp_tests.dir\catch_main.cpp.obj
picomp_tests.exe: CMakeFiles\picomp_tests.dir\catch_tests_picomp.cpp.obj
picomp_tests.exe: CMakeFiles\picomp_tests.dir\build.make
picomp_tests.exe: tools\same_stats_tools.lib
picomp_tests.exe: CMakeFiles\picomp_tests.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\testing_with_catch - Kopie - Kopie\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable picomp_tests.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\picomp_tests.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\picomp_tests.dir\objects1.rsp @<<
 /out:picomp_tests.exe /implib:picomp_tests.lib /pdb:"D:\testing_with_catch - Kopie - Kopie\cmake-build-debug\picomp_tests.pdb" /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  tools\same_stats_tools.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\picomp_tests.dir\build: picomp_tests.exe
.PHONY : CMakeFiles\picomp_tests.dir\build

CMakeFiles\picomp_tests.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\picomp_tests.dir\cmake_clean.cmake
.PHONY : CMakeFiles\picomp_tests.dir\clean

CMakeFiles\picomp_tests.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "D:\testing_with_catch - Kopie - Kopie" "D:\testing_with_catch - Kopie - Kopie" "D:\testing_with_catch - Kopie - Kopie\cmake-build-debug" "D:\testing_with_catch - Kopie - Kopie\cmake-build-debug" "D:\testing_with_catch - Kopie - Kopie\cmake-build-debug\CMakeFiles\picomp_tests.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\picomp_tests.dir\depend

