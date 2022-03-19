# Project:  Maturitni projekt šachy
# Author:   Jakub Urbanek
# Year:     2022

CC = gcc
CFLAGS = -Wall -g -O3
LIBS= -lm


OBJFILES= main.o move_counter.o game.o evaluation.o chess_logic.o chess_structs.o

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


valgrind_test:
	cd bin; \
	valgrind ./chess -d < ../$(TESTDIR)/valgrind_test_in.txt


#using inittial position and position 5 from this site:
#https://www.chessprogramming.org/Perft_Results
move_counter_test:
	cd bin; \
	for i in 1 2 3 4 5 6; do \
		echo "-----------------test$$i--------------------"; \
		./chess -c < ../$(TESTDIR)/move_counter_test_in$$i.txt; \
		echo "correct:"; \
		tail -5 ../$(TESTDIR)/move_counter_test_in$$i.txt; \
		echo "\n";\
	done
	
#it's soooo bad