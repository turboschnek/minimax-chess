# Projekt: Maturitni projekt šachy
# Autor:   Jakub Urbanek
# Rok:     2022

CC = gcc
CFLAGS = -Wall -g -Werror=implicit-function-declaration -O3
LIBS= -lm


OBJFILES= main.o game.o chess.o


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
