# Project:  Maturitni projekt šachy
# Author:   Jakub Urbanek
# Year:     2022

CC = gcc
CFLAGS = -Wall -g -O3
LIBS= -lm


OBJFILES= main.o game.o evaluation.o chess_logic.o chess_structs.o

SRCDIR= src
BINDIR= bin
BINNAME= chess


TESTDIR= test_scenarios

default: build clean


build: makedir $(OBJFILES)
	$(CC) $(CFLAGS) $(LIBS) $(OBJFILES) -o $(BINDIR)/$(BINNAME)


%.o : $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@


makedir:
	rm -rf $(BINDIR)
	mkdir $(BINDIR)


clean:
	rm -f $(OBJFILES)


valgrind-test:
	cd bin; \
	valgrind ./chess -d < ../$(TESTDIR)/valgrind_test_in.txt
