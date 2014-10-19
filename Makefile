# Makefile for Parallel Program 1.

# Author: Charles Parsons
# Written Fall 2014

# Usage:  make

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -O -Wall
CXXFLAGS = -O -Wall

# Pthread library for Linux:
LIBS = -lpthread

#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:	trapezoid trapezoid_timed philosopher_no_lock philosopher_lock

# specific targets
trapezoid:	trapezoid.c
	$(CC) -o $@ $^ $(LIBS)

trapezoid_timed:	trapezoid_timed.c
	$(CC) -o $@ $^ $(LIBS)

philosopher_no_lock:	philosopher_no_lock.c phil_queue.c phil_queue.h
	$(CC) -o $@ $^ $(LIBS)

philosopher_lock:	philosopher_lock.c phil_queue.c phil_queue.h
	$(CC) -o $@ $^ -DSTACK $(LIBS)


# utility targets
clean:
	rm -f *.o *~ core
