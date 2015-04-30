#Daniel Eisterhold
#dte130030@utdallas.edu
#CS 3376.502
CXX = g++
CFLAGS = -Wall
EXECNAME = program3

all: main

main: main.cc
	$(CXX) $(CFLAGS) main.cc -o $(EXECNAME)

clean:
	@rm -f *.o *~

clean-all: clean
	@rm -f $(EXECNAME)
