#Daniel Eisterhold
#CS4348 Project 3
#10 November 2015

PROJECT_NAME=project

CXX=g++
CFLAGS=-Wall -c -g -I ./
LFLAGS=-Wall -lpthread -lrt

OBJS=main.cc.o Server.cc.o FileManager.cc.o Client.cc.o

all: $(PROJECT_NAME) link clean

$(PROJECT_NAME): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@

main.cc.o: main.cc FileManager.h
	$(CXX) $(CFLAGS) main.cc -o $@

Server.cc.o: Server.h Server.cc
	$(CXX) $(CFLAGS) Server.cc -o $@

FileManager.cc.o: FileManager.h FileManager.h
	$(CXX) $(CFLAGS) FileManager.cc -o $@

Client.cc.o: Client.h Client.cc
	$(CXX) $(CFLAGS) Client.cc -o $@

File.cc.o: File.h File.cc
	$(CXX) $(CFLAGS) File.cc -o $@

link:
	@ln -fs $(PROJECT_NAME) server
	@ln -fs $(PROJECT_NAME) client

clean:
	@rm -f *~ \#*

clean-all: clean
	@rm -f client server $(PROJECT_NAME) $(OBJS)