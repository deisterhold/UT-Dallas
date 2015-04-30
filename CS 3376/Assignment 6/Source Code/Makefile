#Daniel Eisterhold
#dte130030@utdallas.edu
#CS 3376.502
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = CS3376.502.Program_6

#Settings for gcc
CXX = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

#Name of Executable
EXECNAME = cs3376thread

#List of Objects need to create executable
OBJS = main.o matrix.o worker.o

#Location of libraries to link in
LDFLAGS = -L /usr/lib

#Name of libraries needed
#LDLIBS = -l cryptopp -l rudeconfig
LDLIBS = -l curses -l cdk -l boost_thread-mt -l boost_system
CLIBS = -I /home/username/include

all: $(EXECNAME) clean

$(EXECNAME): $(OBJS)
	$(CXX) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

main.o: main.cc	Matrix.h Worker.h
	$(CXX) $(CFLAGS) main.cc $(CLIBS) -o $@

matrix.o: Matrix.cc
	$(CXX) $(CFLAGS) Matrix.cc $(CLIBS) -o $@

worker.o: Worker.cc
	$(CXX) $(CFLAGS) Worker.cc $(CLIBS) -o $@

clean:
	@rm -f $(OBJS) *~ \#*

clean-all: clean
	@rm -f $(EXECNAME)

tar:
	tar -cvf $(EXECNAME).tar.gz *

backup:
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
