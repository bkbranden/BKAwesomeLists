# Variables are set with "=", VARNAME=value
CXX=clang++

# Use this variable for compiler flags
CXXFLAGS= -Wall -O2 -std=c++17 -I /usr/local/include/boost_1_73_0

objects = *.o

cppfiles = *.cpp


# "@" symbol prevents the actual command from getting printed out
.DELETE_ON_ERROR:
all: program
	@echo
	@echo "PROGRAM EXECUTION======================================================================="
	@echo
	@./program

debug: CXXFLAGS += -D_DEBUG -g 
debug: all

.PHONY: all

program: ofiles
	$(CXX) $(CXXFLAGS) $(objects) -o program

ofiles: $(cppfiles)
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm *.o program *.gch
