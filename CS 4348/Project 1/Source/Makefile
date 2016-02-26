#Daniel Eisterhold
#dte130030@utdallas.edu
#CS 4348.001
#Project 1

EXECNAME= project

CXX=g++

CFLAGS= -Wall -c
LFLAGS= -Wall
LDFLAGS=

OBJS= main.cc.o CPU.cc.o Memory.cc.o BUS.cc.o FIFO.cc.o MemoryLoader.cc.o

all: $(EXECNAME) clean

$(EXECNAME): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@ $(LDFLAGS)

main.cc.o: main.cc CPU.h Memory.h
	$(CXX) $(CFLAGS) main.cc -o $@

Memory.cc.o: Memory.h Memory.cc BUS.h MemoryLoader.h
	$(CXX) $(CFLAGS) Memory.cc -o $@

CPU.cc.o: CPU.h CPU.cc BUS.h
	$(CXX) $(CFLAGS) CPU.cc -o $@

BUS.cc.o: BUS.h BUS.cc FIFO.h
	$(CXX) $(CFLAGS) BUS.cc -o $@

FIFO.cc.o: FIFO.h FIFO.cc
	$(CXX) $(CFLAGS) FIFO.cc -o $@

MemoryLoader.cc.o: MemoryLoader.h MemoryLoader.cc
	$(CXX) $(CFLAGS) MemoryLoader.cc -o $@

clean:
	@rm -f \#* *~

clean-all: clean
	@rm -f $(EXECNAME) *.o