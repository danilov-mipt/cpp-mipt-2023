CXXFLAGS=-std=c++17 -Wall -Wpedantic -O3
CXX=clang++

.PHONY: all clean

all: main 

main: ./src/main.cpp
	$(CXX) -o main $(CXXFLAGS) ./src/main.cpp -lsqlite3
