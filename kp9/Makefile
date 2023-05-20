CC = gcc
CFLAGS = -g -std=c99 -w -pipe -O3

all: myprogram
myprogram: main.o table.o
	$(CC) $(CFLAGS) -o myprogram main.o table.o
main.o: main.c table.h
	$(CC) $(CFLAGS) -c main.c
mystack.o: table.c table.h
	$(CC) $(CFLAGS) -c table.c
clean:
	rm -f myprogram *.o
