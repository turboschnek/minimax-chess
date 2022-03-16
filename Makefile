# Project:  Maturitni projekt šachy
# Author:   Jakub Urbanek
# Year:     2022

CC = gcc
CFLAGS = -Wall -g -O3
LIBS= -lm


OBJFILES= main.o game.o evaluation.o chess.o chess_structs.o


BINDIR= bin
BIN= chess


default: build clean
	
build: makedir $(OBJFILES)
	$(CC) $(CFLAGS) $(LIBS) $(OBJFILES) -o $(BINDIR)/$(BIN)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

makedir:
	rm -rf $(BINDIR)
	mkdir $(BINDIR)

clean:
	rm -f $(OBJFILES)
