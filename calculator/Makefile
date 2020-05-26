# C++ compiler
CXX = clang++
CXXFLAGS = -std=c++14

# source code: all files with .cpp extension
SRC = $(wildcard *.cpp)

# object files: take source file stems and replace extension with .o
OBJ = $(SRC:%.cpp=%.o)

# name of executable program
TARGET = main

# there aren't actually any targets called `all` or `clean`
.PHONY: all clean

# first rule is carried out by default
all: $(TARGET)

# link all object files to form executable
$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

# given a single source file, compile to an object file (built-in)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# add dependencies here, e.g. main: header.h
main.o: calculator.h
calculator.o: calculator.h constants.h tokens.h variables.h
tokens.o: constants.h tokens.h
variables.o: variables.h

# remove "auxilliary" files	
clean:
	rm $(TARGET) $(OBJ)