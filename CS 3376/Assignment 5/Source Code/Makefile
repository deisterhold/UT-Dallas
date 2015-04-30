#Daniel Eisterhold
#dte130030@utdallas.edu
#CS 3376.502
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = CS3376.502.Program_5

#Settings for gcc
CXX = g++
CFLAGS = -Wall -c
LFLAGS = -Wall -static
#Name of Executable
EXECNAME = cs3376dirmond

#List of Objects need to create executable
OBJS = main.o parseCommandLine.o parseConfigFile.o fileHandler.o logger.o

#Location of libraries to link in
LDFLAGS = -L /usr/lib

#Name of libraries needed
LDLIBS = -l cryptopp -l rudeconfig
CLIBS = -I /home/username/include

all: $(EXECNAME) clean

$(EXECNAME): $(OBJS)
	$(CXX) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

main.o: main.cc FileHandler.h
	$(CXX) $(CFLAGS) main.cc $(CLIBS) -o $@

parseCommandLine.o: parseCommandLine.cc
	$(CXX) $(CFLAGS) parseCommandLine.cc $(CLIBS) -o $@

parseConfigFile.o: parseConfigFile.cc
	$(CXX) $(CFLAGS) parseConfigFile.cc $(CLIBS) -o $@

fileHandler.o: FileHandler.cc Logger.h
	$(CXX) $(CFLAGS) FileHandler.cc $(CLIBS) -o $@

logger.o: Logger.cc
	$(CXX) $(CFLAGS) Logger.cc $(CLIBS) -o $@

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
