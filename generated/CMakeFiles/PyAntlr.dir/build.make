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
CMAKE_SOURCE_DIR = /home/unix/Python-Interpreter-2023

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/unix/Python-Interpreter-2023

# Include any dependencies generated for this target.
include generated/CMakeFiles/PyAntlr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include generated/CMakeFiles/PyAntlr.dir/compiler_depend.make

# Include the progress variables for this target.
include generated/CMakeFiles/PyAntlr.dir/progress.make

# Include the compile flags for this target's objects.
include generated/CMakeFiles/PyAntlr.dir/flags.make

generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o: generated/CMakeFiles/PyAntlr.dir/flags.make
generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o: generated/Python3Lexer.cpp
generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o: generated/CMakeFiles/PyAntlr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/unix/Python-Interpreter-2023/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o -MF CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o.d -o CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o -c /home/unix/Python-Interpreter-2023/generated/Python3Lexer.cpp

generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.i"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/unix/Python-Interpreter-2023/generated/Python3Lexer.cpp > CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.i

generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.s"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/unix/Python-Interpreter-2023/generated/Python3Lexer.cpp -o CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.s

generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o: generated/CMakeFiles/PyAntlr.dir/flags.make
generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o: generated/Python3Parser.cpp
generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o: generated/CMakeFiles/PyAntlr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/unix/Python-Interpreter-2023/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o -MF CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o.d -o CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o -c /home/unix/Python-Interpreter-2023/generated/Python3Parser.cpp

generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PyAntlr.dir/Python3Parser.cpp.i"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/unix/Python-Interpreter-2023/generated/Python3Parser.cpp > CMakeFiles/PyAntlr.dir/Python3Parser.cpp.i

generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PyAntlr.dir/Python3Parser.cpp.s"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/unix/Python-Interpreter-2023/generated/Python3Parser.cpp -o CMakeFiles/PyAntlr.dir/Python3Parser.cpp.s

generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o: generated/CMakeFiles/PyAntlr.dir/flags.make
generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o: generated/Python3ParserBaseVisitor.cpp
generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o: generated/CMakeFiles/PyAntlr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/unix/Python-Interpreter-2023/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o -MF CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o.d -o CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o -c /home/unix/Python-Interpreter-2023/generated/Python3ParserBaseVisitor.cpp

generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.i"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/unix/Python-Interpreter-2023/generated/Python3ParserBaseVisitor.cpp > CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.i

generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.s"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/unix/Python-Interpreter-2023/generated/Python3ParserBaseVisitor.cpp -o CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.s

generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o: generated/CMakeFiles/PyAntlr.dir/flags.make
generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o: generated/Python3ParserVisitor.cpp
generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o: generated/CMakeFiles/PyAntlr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/unix/Python-Interpreter-2023/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o -MF CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o.d -o CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o -c /home/unix/Python-Interpreter-2023/generated/Python3ParserVisitor.cpp

generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.i"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/unix/Python-Interpreter-2023/generated/Python3ParserVisitor.cpp > CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.i

generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.s"
	cd /home/unix/Python-Interpreter-2023/generated && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/unix/Python-Interpreter-2023/generated/Python3ParserVisitor.cpp -o CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.s

# Object files for target PyAntlr
PyAntlr_OBJECTS = \
"CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o" \
"CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o" \
"CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o" \
"CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o"

# External object files for target PyAntlr
PyAntlr_EXTERNAL_OBJECTS =

generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/Python3Lexer.cpp.o
generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/Python3Parser.cpp.o
generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/Python3ParserBaseVisitor.cpp.o
generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/Python3ParserVisitor.cpp.o
generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/build.make
generated/libPyAntlr.a: generated/CMakeFiles/PyAntlr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/unix/Python-Interpreter-2023/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libPyAntlr.a"
	cd /home/unix/Python-Interpreter-2023/generated && $(CMAKE_COMMAND) -P CMakeFiles/PyAntlr.dir/cmake_clean_target.cmake
	cd /home/unix/Python-Interpreter-2023/generated && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PyAntlr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
generated/CMakeFiles/PyAntlr.dir/build: generated/libPyAntlr.a
.PHONY : generated/CMakeFiles/PyAntlr.dir/build

generated/CMakeFiles/PyAntlr.dir/clean:
	cd /home/unix/Python-Interpreter-2023/generated && $(CMAKE_COMMAND) -P CMakeFiles/PyAntlr.dir/cmake_clean.cmake
.PHONY : generated/CMakeFiles/PyAntlr.dir/clean

generated/CMakeFiles/PyAntlr.dir/depend:
	cd /home/unix/Python-Interpreter-2023 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/unix/Python-Interpreter-2023 /home/unix/Python-Interpreter-2023/generated /home/unix/Python-Interpreter-2023 /home/unix/Python-Interpreter-2023/generated /home/unix/Python-Interpreter-2023/generated/CMakeFiles/PyAntlr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : generated/CMakeFiles/PyAntlr.dir/depend

