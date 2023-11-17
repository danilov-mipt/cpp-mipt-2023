# This Makefile builds catch v2 core and tests for
# my implementation of Gilded Rose

LANG=C
LIBS= 
CXXFLAGS=-std=c++17 -Wall -Wpedantic -fsanitize=address,undefined
CXX=clang++

all: tests

tests: catch_main.o tests.o
	$(CXX) -o tests $(CXXFLAGS) tests.o catch_main.o
	
tests.o: tests.cpp catch.hpp gilded_rose.hpp
	$(CXX) -c $(CXXFLAGS) tests.cpp

catch_main.o: catch_main.cpp catch.hpp
	$(CXX) -c $(CXXFLAGS) catch_main.cpp

.PHONY: clean
clean:
	rm tests.o catch_main.o

