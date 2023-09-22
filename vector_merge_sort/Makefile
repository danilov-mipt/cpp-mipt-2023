# This Makefile treats every *.cpp file as individual target.
# It stores resulting binaries in bin/ subdirectory.

LANG=C
LIBS= 
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,undefined
CXX=clang++

all: tests

tests: catch_main.o tests.o
	$(CXX) -o tests $(CXXFLAGS) tests.o catch_main.o
	
tests.o: tests.cpp catch.hpp Vector.hpp MergeSort.hpp
	$(CXX) -c $(CXXFLAGS) tests.cpp

catch_main.o: catch_main.cpp catch.hpp
	$(CXX) -c $(CXXFLAGS) catch_main.cpp

#main: main.o
#	$(CXX) -o main $(CXXFLAGS) main.o

#main.o: main.cpp Vector.hpp MergeSort.hpp
#	$(CXX) -c $(CXXFLAGS) main.cpp

.PHONY: clean
clean:
	rm tests.o catch_main.o

