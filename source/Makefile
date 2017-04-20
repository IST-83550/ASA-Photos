CC=gcc
CFLAGS=-g -Wall -pedantic

all: main

main: main.o graph.o
	$(CC) -o main main.o graph.o

main.o: graph.c main.c
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.h graph.c
	$(CC) $(CFLAGS) -c graph.c

clean:
	$(RM) *.o main