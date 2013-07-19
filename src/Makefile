# Makefile for the SAMOA project
# To compile all new files, run make. To clear all object files and executable,
# run make clean.
# We assume that the Raspberry Pi has the wiringPi library installed on it.
# The wiringPi library, along with instructions to download and install can be
# found at wiringpi.com.
# For now, this Makefile is intended to be in the source directory with all
# source files.
# Authors: Leighanne Hsu
#	Chris Hudson
# Last modified: July 9, 2013


# Compiler and linker flags
CFLAGS=-c -g -l wiringPi
LDFLAGS=-l wiringPi

# All .cpp source and object files
CPPSOURCES=AR_DRONE.cpp Controler.cpp  diagnostics.cpp \
	 XbeeIO.cpp filter.cpp
CPPOBJECTS=$(CPPSOURCES:.cpp=.o)

# All .c source and object files
CSOURCES=scan.c sonar.c UDP.c
COBJECTS=$(CSOURCES:.c=.o)

# Location of the source files in relation to the Makefile. Separate multiple
# locations using :
VPATH=.

# Change name of executable file here
EXECUTABLE=testrun


# The default target
all: $(CSOURCES) $(CPPSOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(CPPOBJECTS) $(COBJECTS)
	g++ $(LDFLAGS) $(CPPOBJECTS) $(COBJECTS) -o $@

.cpp.o:
	g++ $(CFLAGS) $< -o $@
.c.o:
	gcc $(CFLAGS) $< -o $@


# Indicates target is not the name of a file. Separate multiple targets with
# spaces.
.PHONY: clean
clean:
	rm -rf $(wildcard *.o) $(EXECUTABLE)
