CXX      = g++
FLAGS    = -g -Wall  
STD      = -std=c++20
INCLUDES = -I. 
DEBUG    = -DDEBUG=0
OBJFILES = object_state.o computational_maths.o vector.o wgs84.o utilities.o main.o 


all: main

%.o: src/%.cpp
	$(CXX) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -c $^

.PHONY: main
main: $(OBJFILES) 
	$(CXX) $(DEBUG) $(FLAGS) $(INCLUDES) $(STD) -o $@ $^ 
	mv $^ ./bin/
	mv $@ ./bin/

.PHONY: clean
clean:
	@rm -f ./bin/*
