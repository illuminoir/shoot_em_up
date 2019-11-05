# Makefile TP2 C

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall -ansi -pedantic


entiers: entiers.c
	$(CC) -o $@ $^ $(CFLAGS)


clean: