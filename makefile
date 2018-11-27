##
# PROGRAM:    Assignment 7
# PROGRAMMER: Tyler Saballus
# LOGON ID:   z1836409
# DATE DUE:   11-30-2018
#

# Compiler variables
CC = g++
CCFLAGS = -Wall

# Rule to link object code files to create executable file
Assign7: hw7.o entry.o
	$(CC) $(CCFLAGS) -o Assign7 hw7.o entry.cc

# Rules to compile source code file to object code
hw7.o: hw7.cc
	$(CC) $(CCFLAGS) -c hw7.cc

entry.o: entry.cc entry.h
	$(CC) $(CCFLAGS) -c entry.cc

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign7
