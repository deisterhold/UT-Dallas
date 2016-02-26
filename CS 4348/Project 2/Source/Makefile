#Daniel Eisterhold
#CS4348 Project 2
#13 October 2015

PROJECT_NAME=project

CXX=g++
CFLAGS=-Wall -c -g
LFLAGS=-Wall -l pthread

OBJS= main.cc.o FrontDesk.cc FrontDeskEmployee.cc.o Guest.cc.o Bellhop.cc.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@

main.cc.o: main.cc FrontDesk.h
	$(CXX) $(CFLAGS) main.cc -o $@

FrontDesk.cc.o: FrontDesk.h FrontDesk.cc FrontDeskEmployee.h
	$(CXX) $(CFLAGS) FrontDesk.cc -o $@

FrontDeskEmployee.cc.o: FrontDeskEmployee.h FrontDeskEmployee.cc Bellhop.h
	$(CXX) $(CFLAGS) FrontDeskEmployee.cc -o $@

Guest.cc.o: Guest.h Guest.cc
	$(CXX) $(CFLAGS) Guest.cc -o $@

Bellhop.cc.o: Bellhop.h Bellhop.cc Guest.h
	$(CXX) $(CFLAGS) Bellhop.cc -o $@

clean:
	@rm -f *~ *#

clean-all: clean
	@rm -f *.o $(PROJECT_NAME)