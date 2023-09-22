# This Makefile treats every *.cpp file as individual target.
# It stores resulting binaries in bin/ subdirectory.

LANG=C
LIBS= 
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,undefined -pedantic
CXX=clang++

SRCS = $(wildcard *.cpp)

PROGS = $(patsubst %.cpp,%,$(SRCS))

BINDIR = ./bin

all: bindir $(PROGS)

%: %.cpp
	$(CXX) -o $(BINDIR)/$@ $< $(CXXFLAGS)

bindir:
	@mkdir -p $(BINDIR)

.PHONY: clean
clean:
	rm -r $(BINDIR)
